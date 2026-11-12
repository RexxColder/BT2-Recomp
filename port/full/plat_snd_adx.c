/*
 * Sonido de BT2, capa de musica/voces: la parte de la API publica ADXT_* de CRI que llama el juego, sustituida en el lado EE
 * (docs/AUDIO_PLAN.md). Adaptado de port/full/gs/snd_adx.c (Tenkaichi 3). Las direcciones son las de BT2 (func_ + direccion):
 *   0x2F39D8 ADXT_Create        0x2F5858 ADXT_SetReloadSct   0x2F5620 ADXT_SetSvrFreq   0x2F7040 ADXT_StartAfs
 *   0x2F72A0 ADXT_StartFname    0x2F44A0 ADXT_Stop           0x2F6230 ADXT_Pause        0x2F52A8 ADXT_SetOutVol
 *   0x2F5358 ADXT_GetOutVol     0x2F4F88 ADXT_SetOutPan      0x2F6D90 ADXT_SetOutputMono 0x2F4590 ADXT_GetStat
 * Los archivos ADX salen de los AFS (plat_file.c: Port_ReadAudioFile). Decodificacion ADX 4 bits aqui; salida por SDL3, un
 * SDL_AudioStream por reproductor. Sin dispositivo de audio todo sigue "parado" (modo silencioso, no se cae).
 * Variables: BT2_NOSOUND=1 sin audio; BT2_SOUND=1 audio aunque no haya ventana; BT2_AUDIO_DUMP=<f.wav> escribe tambien la
 * mezcla final (post-mezcla del dispositivo) a un WAV; BT2_SND_VERBOSE=1 traza.
 */
#include <SDL3/SDL.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned gGsFrame;
extern int GsGpu_Enabled(void) __attribute__((weak));
extern int gPortMusicPercent, gPortSePercent;
extern uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, uint32_t *outSize); /* plat_file.c */

enum { ADXT_STAT_STOP = 0, ADXT_STAT_PLAYING = 3, ADXT_STAT_PLAYEND = 5 };
#define MAX_PLAYERS 16
#define FRAME 18
#define PAN_AUTO (-128)

typedef struct Player {
    SDL_AudioStream *stream;
    uint8_t *file;          /* the whole ADX file */
    uint32_t size, data;    /* file size; offset of the first frame */
    uint32_t channels, rate, total;
    int loop;
    uint32_t loopStart, loopEnd; /* samples */
    uint32_t pos;           /* next sample */
    int c1, c2;
    int hist[2][2];
    int stat, paused;
    int vol;                /* 0.1 dB, 0 = full, -960 and below = silent */
    int pan[2];             /* per input channel: -15 left .. 15 right, PAN_AUTO */
} Player;

static Player sPlayers[MAX_PLAYERS];
static int sCount;
static SDL_AudioDeviceID sDevice;
static int sMono, sTried;
static unsigned sFeedCalls; /* callbacks from SDL so far (BT2_SND_VERBOSE prints it at a stop) */


static uint32_t be32(const uint8_t *p) { return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3]; }
static uint32_t be16(const uint8_t *p) { return (uint32_t)p[0] << 8 | p[1]; }

/* ---- volcado de la mezcla final a WAV (BT2_AUDIO_DUMP=<f.wav>): callback de post-mezcla del dispositivo SDL */
static FILE *sWav;
static uint32_t sWavBytes, sWavRate, sWavCh;
static unsigned sWavNext;
static void wav_header(void) {
    uint8_t h[44];
    uint32_t v;
    memcpy(h, "RIFF", 4); v = 36 + sWavBytes; memcpy(h + 4, &v, 4); memcpy(h + 8, "WAVEfmt ", 8);
    v = 16; memcpy(h + 16, &v, 4);
    h[20] = 1; h[21] = 0; h[22] = (uint8_t)sWavCh; h[23] = 0;
    memcpy(h + 24, &sWavRate, 4); v = sWavRate * sWavCh * 2; memcpy(h + 28, &v, 4);
    h[32] = (uint8_t)(sWavCh * 2); h[33] = 0; h[34] = 16; h[35] = 0;
    memcpy(h + 36, "data", 4); memcpy(h + 40, &sWavBytes, 4);
    fseek(sWav, 0, SEEK_SET); fwrite(h, 1, 44, sWav); fseek(sWav, 0, SEEK_END); fflush(sWav);
}
static void SDLCALL postmix(void *user, const SDL_AudioSpec *spec, float *buf, int buflen) {
    int n = buflen / 4, i;
    int16_t tmp[2048];
    (void)user;
    if (!sWav) return;
    if (!sWavRate) { sWavRate = (uint32_t)spec->freq; sWavCh = (uint32_t)spec->channels; wav_header(); }
    while (n > 0) {
        int c = n > 2048 ? 2048 : n;
        for (i = 0; i < c; i++) { float v = buf[i] * 32767.0f; tmp[i] = (int16_t)(v > 32767.0f ? 32767.0f : v < -32768.0f ? -32768.0f : v); }
        fwrite(tmp, 2, (size_t)c, sWav); sWavBytes += (uint32_t)c * 2;
        buf += c; n -= c;
    }
    if (++sWavNext % 50 == 0) wav_header();
}
static void wav_close(void) { if (sWav) { if (sWavRate) wav_header(); fclose(sWav); sWav = NULL; } }

static int device(void) {
    /* no antes de que el renderer decida si hay ventana (su primer cuadro) */
    int gpu = GsGpu_Enabled && GsGpu_Enabled();
    const char *dump = getenv("BT2_AUDIO_DUMP");
    if (!sTried && (gpu || dump || getenv("BT2_SOUND") != NULL || gGsFrame > 2)) {
        sTried = 1;
        if ((gpu || dump || getenv("BT2_SOUND") != NULL) && getenv("BT2_NOSOUND") == NULL && SDL_InitSubSystem(SDL_INIT_AUDIO)) {
            sDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
            if (sDevice == 0) {
                fprintf(stderr, "bt2: sin dispositivo de audio (modo silencioso): %s\n", SDL_GetError());
            }
            else {
                if (dump && (sWav = fopen(dump, "wb")) != NULL) {
                    uint8_t z[44] = {0};
                    fwrite(z, 1, 44, sWav);
                    SDL_SetAudioPostmixCallback(sDevice, postmix, NULL);
                    atexit(wav_close);
                    fprintf(stderr, "bt2: volcado de audio a %s\n", dump);
                }
                SDL_ResumeAudioDevice(sDevice);
                fprintf(stderr, "bt2: sonido: %s\n", SDL_GetCurrentAudioDriver());
            }
        } else if (getenv("BT2_NOSOUND") == NULL) {
            fprintf(stderr, "bt2: sin audio (modo silencioso)\n");
        }
    }
    return sDevice != 0;
}

/* Lo que mezcla el resto del port: el dispositivo abierto, o 0. */
unsigned Port_AudioDevice(void) {
    return device() ? (unsigned)sDevice : 0;
}

static void adx_coefs(uint32_t highpass, uint32_t rate, int *c1, int *c2) {
    double z = cos(2.0 * 3.14159265358979323846 * (double)highpass / (double)rate);
    double a = 1.41421356237309504880 - z, b = 1.41421356237309504880 - 1.0;
    double c = (a - sqrt((a + b) * (a - b))) / b;

    /* 12 fractional bits, truncated toward zero (as vgmstream does; ffmpeg rounds instead, which changes a
       coefficient by at most one unit: its output differed from the floor variant by up to 91 of 32768 over three
       seconds of music, and by nothing on a short clip). Which rounding CRI's own decoder uses was not checked. */
    *c1 = (int)(c * 8192.0);
    *c2 = (int)(c * c * -4096.0);
}

/* Decodes up to `frames` 32-sample frames at p->pos (a multiple of 32) into interleaved stereo; returns samples. */
static int decode(Player *p, int16_t *out, int frames) {
    int n = 0, f, ch, i;
    float gl[2], gr[2];

    for (ch = 0; ch < 2; ch++) { /* pan per input channel */
        int pan = p->pan[ch] != PAN_AUTO ? p->pan[ch] : p->channels == 1 ? 0 : ch == 0 ? -15 : 15;
        if (sMono) { pan = 0; }
        gl[ch] = pan <= 0 ? 1.0f : (float)(15 - pan) / 15.0f;
        gr[ch] = pan >= 0 ? 1.0f : (float)(15 + pan) / 15.0f;
    }
    for (f = 0; f < frames; f++) {
        uint32_t end = p->loop ? p->loopEnd : p->total, index = p->pos / 32;
        int16_t pcm[2][32];
        const uint8_t *src = p->file + p->data + (size_t)index * FRAME * p->channels;
        int count;

        if (p->pos >= end) {
            if (!p->loop) {
                break;
            }
            p->pos = p->loopStart & ~31u; /* loop starts are frame-aligned by the encoder */
            continue;
        }
        if (src + FRAME * p->channels > p->file + p->size) {
            p->loop = 0;
            p->total = p->pos;
            break;
        }
        for (ch = 0; ch < (int)p->channels; ch++, src += FRAME) {
            int scale = (int)be16(src) + 1, h1 = p->hist[ch][0], h2 = p->hist[ch][1];
            for (i = 0; i < 32; i++) {
                int nib = (src[2 + i / 2] >> ((i & 1) ? 0 : 4)) & 15, s;
                if (nib & 8) { nib -= 16; }
                s = nib * scale + ((p->c1 * h1 + p->c2 * h2) >> 12);
                if (s > 32767) { s = 32767; }
                if (s < -32768) { s = -32768; }
                pcm[ch][i] = (int16_t)s;
                h2 = h1;
                h1 = s;
            }
            p->hist[ch][0] = h1;
            p->hist[ch][1] = h2;
        }
        count = (int)(end - p->pos < 32 ? end - p->pos : 32);
        for (i = (int)(p->pos & 31); i < count; i++) {
            float l, r;
            if (p->channels == 1) {
                l = (float)pcm[0][i] * gl[0];
                r = (float)pcm[0][i] * gr[0];
            } else {
                l = (float)pcm[0][i] * gl[0] + (float)pcm[1][i] * gl[1];
                r = (float)pcm[0][i] * gr[0] + (float)pcm[1][i] * gr[1];
            }
            out[n * 2] = (int16_t)(l > 32767.0f ? 32767.0f : l < -32768.0f ? -32768.0f : l);
            out[n * 2 + 1] = (int16_t)(r > 32767.0f ? 32767.0f : r < -32768.0f ? -32768.0f : r);
            n++;
        }
        p->pos = (p->pos & ~31u) + 32;
    }
    return n;
}

/* SDL's audio thread wants `additional` more bytes from this player (the stream is locked while this runs). */
static void SDLCALL feed(void *user, SDL_AudioStream *stream, int additional, int total) {
    Player *p = user;
    int16_t buf[32 * 2 * 16];

    sFeedCalls++;

    (void)total;
    while (additional > 0 && p->stat == ADXT_STAT_PLAYING && !p->paused) {
        int n = decode(p, buf, 16);
        if (n == 0) {
            p->stat = ADXT_STAT_PLAYEND;
            break;
        }
        SDL_PutAudioStreamData(stream, buf, n * 4);
        additional -= n * 4;
    }
}


static void apply_volume(Player *p) {
    if (p->stream != NULL) {
        SDL_SetAudioStreamGain(p->stream, p->vol <= -960 ? 0.0f : (float)pow(10.0, (double)p->vol / 200.0) * (float)gPortMusicPercent / 100.0f);
    }
}

static void stop(Player *p) {
    if (p->stream != NULL && getenv("BT2_SND_VERBOSE") != NULL) {
        fprintf(stderr, "adx: stop player %d at %.1f s, status %d, volume %d; %u callbacks so far\n", (int)(p - sPlayers), (double)p->pos / (double)p->rate, p->stat, p->vol, sFeedCalls);
    }
    if (p->stream != NULL) {
        SDL_DestroyAudioStream(p->stream); /* waits for a running callback */
        p->stream = NULL;
    }
    free(p->file);
    p->file = NULL;
    p->stat = ADXT_STAT_STOP;
}

static void start(Player *p, int ptid, int flid, const char *fname) {
    SDL_AudioSpec spec;
    uint32_t header, highpass;
    const char *path = fname ? fname : "(afs)";

    stop(p);
    if (!device()) {
        return;
    }
    p->file = Port_ReadAudioFile(ptid, flid, fname, &p->size);
    if (p->file == NULL) {
        fprintf(stderr, "bt2: archivo de sonido no encontrado: (%d,%d) %s\n", ptid, flid, path);
        return;
    }
    if (p->size < 0x40 || be16(p->file) != 0x8000 || p->file[4] != 3 || p->file[5] != FRAME || p->file[6] != 4 ||
        p->file[7] < 1 || p->file[7] > 2 || (p->file[0x13] & 8)) {
        fprintf(stderr, "bt2: (%d,%d) %s no es un ADX del tipo que usa el juego\n", ptid, flid, path);
        free(p->file);
        p->file = NULL;
        return;
    }
    header = be16(p->file + 2) + 4;
    p->data = header;
    p->channels = p->file[7];
    p->rate = be32(p->file + 8);
    p->total = be32(p->file + 12);
    highpass = be16(p->file + 16);
    p->loop = 0;
    if (p->file[0x12] == 4 && header >= 0x38 && be32(p->file + 0x24) != 0) {
        p->loopStart = be32(p->file + 0x28);
        p->loopEnd = be32(p->file + 0x30);
        p->loop = p->loopEnd > p->loopStart && p->loopEnd <= p->total;
    }
    adx_coefs(highpass, p->rate, &p->c1, &p->c2);
    memset(p->hist, 0, sizeof(p->hist));
    p->pos = 0;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = (int)p->rate;
    p->stream = SDL_CreateAudioStream(&spec, NULL);
    if (p->stream == NULL) {
        fprintf(stderr, "bt2: sound stream: %s\n", SDL_GetError());
        return;
    }
    if (getenv("BT2_SND_VERBOSE") != NULL) {
        fprintf(stderr, "adx: start (%d,%d) %s: %u ch, %u Hz, %.1f s, loop %d, volume %d (0.1 dB), paused %d\n", ptid, flid, path, p->channels, p->rate,
                (double)p->total / (double)p->rate, p->loop, p->vol, p->paused);
    }
    p->stat = ADXT_STAT_PLAYING;
    apply_volume(p);
    SDL_SetAudioStreamGetCallback(p->stream, feed, p);
    if (!SDL_BindAudioStream(sDevice, p->stream)) {
        fprintf(stderr, "bt2: sound stream: %s\n", SDL_GetError());
    }
}

/* ------------------------------------------------------------------------------- las funciones de la libreria (EE de BT2) */
/* El juego guarda el manejador en su memoria y alguna ruta lo pasa por una mascara de direcciones del PS2: no puede ser un
   puntero del host. Manejador = HBASE + indice. */
#define HBASE 0x300
static Player *hn(unsigned h) { return (h >= HBASE && h < HBASE + MAX_PLAYERS) ? &sPlayers[h - HBASE] : NULL; }

unsigned func_002F39D8(int maxnch, unsigned work, int worksize) {   /* ADXT_Create */
    Player *p = &sPlayers[sCount < MAX_PLAYERS ? sCount++ : MAX_PLAYERS - 1];
    (void)maxnch; (void)work; (void)worksize;
    memset(p, 0, sizeof(*p));
    p->pan[0] = p->pan[1] = PAN_AUTO;
    return HBASE + (unsigned)(p - sPlayers);
}

void func_002F5858(unsigned adxt, int nsct) { (void)adxt; (void)nsct; }   /* ADXT_SetReloadSct */
void func_002F5620(unsigned adxt, int freq) { (void)adxt; (void)freq; }   /* ADXT_SetSvrFreq */

void func_002F7040(unsigned adxt, int patid, int fid) {                   /* ADXT_StartAfs */
    Player *p = hn(adxt);
    if (p != NULL) start(p, patid, fid, NULL);
}

void func_002F72A0(unsigned adxt, unsigned fname) {                       /* ADXT_StartFname */
    Player *p = hn(adxt);
    if (p != NULL && fname) start(p, 0, 0, (const char *)(uintptr_t)fname);
}

void func_002F44A0(unsigned adxt) {                                       /* ADXT_Stop */
    Player *p = hn(adxt);
    if (p != NULL) stop(p);
}

void func_002F6230(unsigned adxt, int sw) {                               /* ADXT_Pause */
    Player *p = hn(adxt);

    if (p == NULL) {
        return;
    }
    if (getenv("BT2_SND_VERBOSE") != NULL && p->paused != (sw != 0)) {
        fprintf(stderr, "adx: player %d pause %d\n", (int)(p - sPlayers), sw);
    }
    if (p->stream != NULL) {
        SDL_LockAudioStream(p->stream);
        p->paused = sw != 0;
        if (p->paused) {
            SDL_ClearAudioStream(p->stream); /* lo que esta en cola se oiria igual */
        }
        SDL_UnlockAudioStream(p->stream);
    } else {
        p->paused = sw != 0;
    }
}

void func_002F52A8(unsigned adxt, int vol) {                              /* ADXT_SetOutVol */
    Player *p = hn(adxt);
    if (p != NULL) {
        if (getenv("BT2_SND_VERBOSE") != NULL && p->vol != vol) {
            fprintf(stderr, "adx: player %d volume %d\n", (int)(p - sPlayers), vol);
        }
        p->vol = vol;
        apply_volume(p);
    }
}

int func_002F5358(unsigned adxt) {                                        /* ADXT_GetOutVol */
    Player *p = hn(adxt);
    return p != NULL ? p->vol : 0;
}

void func_002F4F88(unsigned adxt, int chan, int pan) {                    /* ADXT_SetOutPan */
    Player *p = hn(adxt);
    if (p != NULL && chan >= 0 && chan < 2) {
        if (p->stream != NULL) { SDL_LockAudioStream(p->stream); }
        p->pan[chan] = pan;
        if (p->stream != NULL) { SDL_UnlockAudioStream(p->stream); }
    }
}

void func_002F6D90(int flag) { sMono = flag != 0; }                       /* ADXT_SetOutputMono */

int func_002F4590(unsigned adxt) {                                        /* ADXT_GetStat */
    Player *p = hn(adxt);
    return p != NULL ? p->stat : ADXT_STAT_STOP;
}


/* ---------------------------------------------------------------------------------------------------------------
   Audio de las peliculas SFD (plat_movie.c): su demuxer entrega el ADX del stream 0x1C0 por paquetes (el primero con la cabecera
   ADX 0x8000..., los demas tramas de 18 bytes por canal, intercaladas). Se decodifica aqui a PCM y se empuja a un SDL_AudioStream
   propio (el reloj es el del dispositivo; la pelicula corre por reloj de pared, asi que arrancan juntos). */
static struct {
    SDL_AudioStream *stream;
    int rate, channels, haveHdr, c1, c2, hist[2][2], pending_end;
    uint8_t carry[64]; int ncarry;
    int64_t t0ns, lastPts;
} sMov;

static void mov_free(void) {
    if (sMov.stream != NULL) { SDL_DestroyAudioStream(sMov.stream); }
    memset(&sMov, 0, sizeof sMov);
}

void Movie_AudioBegin(int sample_rate, int channels) {
    mov_free();
    if (!device() || channels < 1 || channels > 2) { return; }
    {
        SDL_AudioSpec spec;
        spec.format = SDL_AUDIO_S16; spec.channels = channels; spec.freq = sample_rate;
        sMov.stream = SDL_CreateAudioStream(&spec, NULL);
        if (sMov.stream == NULL || !SDL_BindAudioStream(sDevice, sMov.stream)) { mov_free(); return; }
        SDL_SetAudioStreamGain(sMov.stream, (float)gPortMusicPercent / 100.0f);
    }
    sMov.rate = sample_rate; sMov.channels = channels;
    {   struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); sMov.t0ns = (int64_t)ts.tv_sec * 1000000000ll + ts.tv_nsec; }
    if (getenv("BT2_SND_VERBOSE") != NULL) { fprintf(stderr, "movie-audio: begin %d Hz %d ch\n", sample_rate, channels); }
}

static void mov_frames(const uint8_t *src, int nframes) {   /* nframes grupos de `channels` tramas de 18 bytes */
    int16_t out[32 * 2 * 8];
    int f = 0;
    while (f < nframes) {
        int n = nframes - f > 8 ? 8 : nframes - f, k, ch, i;
        for (k = 0; k < n; k++, f++) {
            for (ch = 0; ch < sMov.channels; ch++, src += FRAME) {
                int scale = (int)be16(src) + 1, h1 = sMov.hist[ch][0], h2 = sMov.hist[ch][1];
                for (i = 0; i < 32; i++) {
                    int nib = (src[2 + i / 2] >> ((i & 1) ? 0 : 4)) & 15, v;
                    if (nib & 8) { nib -= 16; }
                    v = nib * scale + ((sMov.c1 * h1 + sMov.c2 * h2) >> 12);
                    if (v > 32767) { v = 32767; }
                    if (v < -32768) { v = -32768; }
                    out[(k * 32 + i) * sMov.channels + ch] = (int16_t)v;
                    h2 = h1; h1 = v;
                }
                sMov.hist[ch][0] = h1; sMov.hist[ch][1] = h2;
            }
        }
        SDL_PutAudioStreamData(sMov.stream, out, n * 32 * sMov.channels * 2);
    }
}

void Movie_AudioPacket(const uint8_t *adx, int len, int64_t pts) {
    int unit, avail;
    uint8_t *buf;
    if (sMov.stream == NULL || len <= 0) { return; }
    sMov.lastPts = pts;
    if (!sMov.haveHdr) {
        uint32_t hp = 500;
        if (len >= 0x20 && be16(adx) == 0x8000) {   /* cabecera ADX al principio del stream */
            uint32_t hdr = be16(adx + 2) + 4;
            if (adx[7] >= 1 && adx[7] <= 2) { sMov.channels = adx[7]; }
            hp = be16(adx + 16);
            if ((int)hdr > len) { return; }
            adx += hdr; len -= (int)hdr;
        }
        adx_coefs(hp, (uint32_t)sMov.rate, &sMov.c1, &sMov.c2);
        sMov.haveHdr = 1;
    }
    unit = FRAME * sMov.channels;
    buf = malloc((size_t)sMov.ncarry + (size_t)len);
    if (buf == NULL) { return; }
    memcpy(buf, sMov.carry, (size_t)sMov.ncarry);
    memcpy(buf + sMov.ncarry, adx, (size_t)len);
    avail = sMov.ncarry + len;
    mov_frames(buf, avail / unit);
    sMov.ncarry = avail % unit;
    memcpy(sMov.carry, buf + avail - sMov.ncarry, (size_t)sMov.ncarry);
    free(buf);
}

void Movie_AudioEnd(void) {
    int64_t now;
    struct timespec ts;
    if (sMov.stream == NULL) { return; }
    clock_gettime(CLOCK_MONOTONIC, &ts);
    now = (int64_t)ts.tv_sec * 1000000000ll + ts.tv_nsec;
    /* termino por si sola (pts del ultimo paquete ~ tiempo transcurrido): dejar vaciar lo que queda; si la saltaron, cortar */
    if (sMov.lastPts / 90 + 700 > (now - sMov.t0ns) / 1000000) {
        SDL_FlushAudioStream(sMov.stream);
        SDL_ClearAudioStream(sMov.stream);
    }
    if (getenv("BT2_SND_VERBOSE") != NULL) { fprintf(stderr, "movie-audio: end (pts %lld ms, wall %lld ms)\n", (long long)(sMov.lastPts / 90), (long long)((now - sMov.t0ns) / 1000000)); }
    mov_free();
}

/* The music volume setting changed: the streams playing now take it over. */
void Port_AudioRefresh(void) {
    int i;
    for (i = 0; i < MAX_PLAYERS; i++) {
        apply_volume(&sPlayers[i]);
    }
}
