/*
 * Sonido de BT2, efectos (SE): el driver del IOP SOUNDS.IRX sustituido en el host (docs/AUDIO_PLAN.md). Adaptado de
 * port/full/gs/snd_se.c (Tenkaichi 3; el protocolo EE<->IOP de snd_298170.c es el mismo en BT2).
 *   - sceSifCallRpc al servidor 0x2000004 (plat_sys.c lo desvia a Port_SndRpc): INIT/RESET/SET_BANK/FREE_BANK/mono/pausa/
 *     volumen/STOP_BANK/QUEUE (cola de <=32 ordenes PLAY/STOP por cuadro).
 *   - sceSifSetDma / sceSifAllocIopHeap: la memoria del IOP es un buffer del host (sIop); las direcciones del IOP son
 *     desplazamientos en el.
 *   - sceSdRemote 0x80D0 (IOP -> RAM del SPU2, sSpu) y 0x80F0 (estado de la transferencia: siempre terminada).
 * Un efecto es "reproducir la muestra N del banco" (cada secuencia es una nota); se decodifica el ADPCM del SPU2 y se mezcla
 * en un SDL_AudioStream propio. Sin dispositivo de audio los comandos se aceptan y no suena nada.
 * Trazas: BT2_SND_VERBOSE=1 (PLAY/bancos), BT2_SND_RPCLOG=1 (cada RPC: funcion, args).
 */
#include <SDL3/SDL.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned gGsFrame;
extern int GsGpu_Enabled(void) __attribute__((weak));

#define SPU_SIZE 0x200000
#define VOICES 48
#define OUT_RATE 48000
/* Loudness of the effects against the music. 0.55 (a guess) was too loud by the user's ear. 0.25 follows the
   chain the console had: sequence volume, note velocity and timbre volume are each 100 of 127 ((100/127)^3 = 0.49)
   and the sound chip's voice volume tops out at half scale. BT2_SE_GAIN=<percent> overrides it for tuning. */
#define SE_GAIN_DEFAULT 0.25f
static float se_gain(void) {
    static float g = -1.0f;
    if (g < 0.0f) {
        g = getenv("BT2_SE_GAIN") != NULL ? (float)atoi(getenv("BT2_SE_GAIN")) / 100.0f : SE_GAIN_DEFAULT;
    }
    return g;
}
extern int gPortSePercent; /* the settings overlay's volume (snd_adx.c); takes effect with the next sound */
#define SE_GAIN (se_gain() * (float)gPortSePercent / 100.0f)

typedef struct Bank {
    int set;
    uint32_t spu;          /* where the sample data is in sSpu */
    const uint8_t *hd, *sq;
    int paused;
    float volume;
} Bank;

typedef struct Voice {
    int on, bank, id, handle;
    uint32_t pos, loopPos;     /* next block / loop start, addresses in sSpu */
    int h1, h2;                /* decoder history */
    int16_t buf[28];
    int have;                  /* samples of buf decoded; 0 = decode the next block first */
    double frac, step;         /* position in buf, input samples per output sample */
    int last, ended;           /* this block is the last one; nothing more to decode */
    int16_t prev;              /* the sample before buf[0], for interpolation */
    float gl, gr;
    float fade;                /* 1 = playing; goes down to 0 after a stop */
    int stopping;
} Voice;

static uint8_t sSpu[SPU_SIZE];

/* ---- memoria del IOP: buffer del host; una "direccion del IOP" es un desplazamiento (el juego solo las pasa de vuelta).
   Reparto de bloques primer-hueco (el juego libera y recarga bancos). */
#define IOP_SIZE (16u << 20)
#define IOP_BASE 0x1000u
#define IOP_BLOCKS 512
static uint8_t *sIop;
static struct { uint32_t addr, size; } sIopBlk[IOP_BLOCKS];
static const uint8_t *iop_ptr(uint32_t a) { return sIop != NULL && a < IOP_SIZE ? sIop + a : NULL; }
/* bytes que quedan en el bloque del IOP que contiene p; 0 si p no está en un bloque */
static uint32_t iop_remain(const uint8_t *p) {
    uintptr_t base, a;
    uint32_t i;
    if (sIop == NULL || p == NULL) return 0;
    base = (uintptr_t)sIop; a = (uintptr_t)p;
    if (a < base || a >= base + IOP_SIZE) return 0;
    a -= base;
    for (i = 0; i < IOP_BLOCKS; i++) {
        if (sIopBlk[i].size && a >= sIopBlk[i].addr && a < sIopBlk[i].addr + sIopBlk[i].size)
            return sIopBlk[i].addr + sIopBlk[i].size - (uint32_t)a;
    }
    return 0;
}
uint32_t Port_IopAlloc(uint32_t size) {
    uint32_t cand = IOP_BASE, i, j;
    if (sIop == NULL) { sIop = calloc(1, IOP_SIZE); if (sIop == NULL) { return 0; } }
    if (size == 0 || size > IOP_SIZE - IOP_BASE) {
        fprintf(stderr, "bt2: pedido de memoria del IOP invalido (0x%X)\n", size);
        return 0;
    }
    size = (size + 63u) & ~63u;
    for (;;) {   /* sube hasta que ningun bloque se solape */
        int moved = 0;
        for (i = 0; i < IOP_BLOCKS; i++) {
            if (sIopBlk[i].size && cand < sIopBlk[i].addr + sIopBlk[i].size && sIopBlk[i].addr < cand + size) { cand = sIopBlk[i].addr + sIopBlk[i].size; moved = 1; }
        }
        if (!moved) { break; }
    }
    if (cand + size > IOP_SIZE) { fprintf(stderr, "bt2: memoria del IOP agotada\n"); return 0; }
    for (j = 0; j < IOP_BLOCKS && sIopBlk[j].size; j++) {}
    if (j == IOP_BLOCKS) { return 0; }
    sIopBlk[j].addr = cand; sIopBlk[j].size = size;
    return cand;
}
void Port_IopFree(uint32_t p) {
    int i;
    for (i = 0; i < IOP_BLOCKS; i++) { if (sIopBlk[i].size && sIopBlk[i].addr == p) { sIopBlk[i].size = 0; } }
}

static Bank sBanks[8];
static Voice sVoices[VOICES];
static SDL_AudioStream *sStream;
static int sMono, sTried;

extern unsigned Port_AudioDevice(void); /* plat_snd_adx.c */

static uint32_t le32(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint32_t le16(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8; }

/* The chunk "SCEI<name>" inside a table (searched over at most `limit` bytes). */
static const uint8_t *chunk(const uint8_t *p, const char *name, uint32_t limit) {
    char tag[8] = {'I', 'E', 'C', 'S', name[3], name[2], name[1], name[0]};
    uint32_t o, rem = iop_remain(p);
    if (rem < limit) limit = rem;
    if (limit < 16) return NULL;
    for (o = 0; o + 16 <= limit; o += 4) {
        if (memcmp(p + o, tag, 8) == 0) return p + o;
    }
    return NULL;
}

/* Sequence number -> where its sample starts, its rate. 0 = no such effect. */
static int lookup(const Bank *b, int id, uint32_t *start, uint32_t *rate) {
    const uint8_t *sesq = chunk(b->sq, "Sesq", 0x4000), *setb = chunk(b->hd, "Setb", 0x8000), *vagi = chunk(b->hd, "Vagi", 0x8000);
    uint32_t timbre = (uint32_t)id, vag, o, rem;
    if (vagi == NULL || iop_remain(vagi) < 0x14) return 0;
    if (sesq != NULL) {
        uint32_t off = 0x34 + 4u * (uint32_t)id;
        if (iop_remain(sesq) >= off + 4) {
            uint32_t so = le32(sesq + off);
            uint32_t srem = iop_remain(sesq);
            if (srem >= 0x14 && so <= srem - 0x14) {
                const uint8_t *seq = sesq + so;
                if (seq[0x11] == 0x90) timbre = seq[0x13];
            }
        }
    }
    vag = timbre;
    rem = iop_remain(setb);
    if (setb != NULL && rem >= 0x23 && timbre <= setb[0x22]) {
        uint32_t off = 0x24 + timbre * (uint32_t)setb[0x20];
        if (rem >= off + 2) vag = le16(setb + off);
    }
    rem = iop_remain(vagi);
    if (vag > le32(vagi + 0x0C)) return 0;
    if (rem < 0x14 + 4u * vag) return 0;
    o = le32(vagi + 0x10 + 4 * vag);
    if (o > rem - 6) return 0;
    *start = b->spu + le32(vagi + o);
    *rate = le16(vagi + o + 4);
    return *start + 16 <= SPU_SIZE && *rate != 0;
}

/* Decodes the voice's next 16-byte block into v->buf. */
static void decode_block(Voice *v) {
    static const int f0[5] = {0, 60, 115, 98, 122}, f1[5] = {0, 0, -52, -55, -60};
    const uint8_t *p;
    int shift, filter, flags, i;

    if (v->last || v->pos + 16 > SPU_SIZE) {
        v->ended = 1;
        v->have = 0;
        return;
    }
    p = &sSpu[v->pos];
    shift = p[0] & 15;
    filter = (p[0] >> 4) & 7;
    flags = p[1];
    if (filter > 4) { filter = 0; }
    if (shift > 12) { shift = 9; } /* what the chip does with the invalid values */
    if (flags & 4) {
        v->loopPos = v->pos;
    }
    v->prev = v->have ? v->buf[27] : 0;
    for (i = 0; i < 28; i++) {
        int nib = (p[2 + i / 2] >> ((i & 1) * 4)) & 15, s;
        if (nib & 8) { nib -= 16; }
        s = ((nib << 12) >> shift) + ((v->h1 * f0[filter] + v->h2 * f1[filter] + 32) >> 6);
        if (s > 32767) { s = 32767; }
        if (s < -32768) { s = -32768; }
        v->buf[i] = (int16_t)s;
        v->h2 = v->h1;
        v->h1 = s;
    }
    v->have = 28;
    v->pos += 16;
    if (flags & 1) {             /* the last block: loop or stop after it */
        if ((flags & 2) && v->loopPos != 0) {
            v->pos = v->loopPos;
        } else {
            v->last = 1;
        }
    }
}

/* SDL's audio thread wants more (the stream is locked while this runs). */
static void SDLCALL mix(void *user, SDL_AudioStream *stream, int additional, int total) {
    int16_t out[512 * 2];
    float acc[512 * 2];
    int frames = additional / 4, n, i, k;

    (void)user; (void)total;
    while (frames > 0) {
        n = frames > 512 ? 512 : frames;
        memset(acc, 0, sizeof(float) * (size_t)n * 2);
        for (k = 0; k < VOICES; k++) {
            Voice *v = &sVoices[k];
            if (!v->on || sBanks[v->bank].paused) {
                continue;
            }
            for (i = 0; i < n; i++) {
                float s, a, b;
                int ip;
                while (v->frac >= (double)v->have) {
                    v->frac -= (double)v->have;
                    decode_block(v);
                    if (v->ended) {
                        break;
                    }
                }
                if (v->ended) {
                    v->on = 0;
                    break;
                }
                ip = (int)v->frac;
                a = (float)(ip == 0 ? v->prev : v->buf[ip - 1]);
                b = (float)v->buf[ip];
                s = (a + (b - a) * (float)(v->frac - (double)ip)) * v->fade;
                acc[i * 2] += s * v->gl;
                acc[i * 2 + 1] += s * v->gr;
                v->frac += v->step;
                if (v->stopping) {
                    v->fade -= 1.0f / (0.008f * OUT_RATE); /* 8 ms */
                    if (v->fade <= 0.0f) {
                        v->on = 0;
                        break;
                    }
                }
            }
        }
        for (i = 0; i < n * 2; i++) {
            float s = acc[i];
            out[i] = (int16_t)(s > 32767.0f ? 32767.0f : s < -32768.0f ? -32768.0f : s);
        }
        SDL_PutAudioStreamData(stream, out, n * 4);
        frames -= n;
    }
}

static int stream_ready(void) {
    if (sStream == NULL && !sTried) {
        SDL_AudioDeviceID dev = (SDL_AudioDeviceID)Port_AudioDevice();
        SDL_AudioSpec spec;

        if (dev == 0) {
            if ((GsGpu_Enabled && GsGpu_Enabled()) || gGsFrame > 2) {
                sTried = 1; /* decided: no device */
            }
            return 0;
        }
        sTried = 1;
        spec.format = SDL_AUDIO_S16;
        spec.channels = 2;
        spec.freq = OUT_RATE;
        sStream = SDL_CreateAudioStream(&spec, NULL);
        if (sStream != NULL) {
            SDL_SetAudioStreamGetCallback(sStream, mix, NULL);
            SDL_BindAudioStream(dev, sStream);
        }
    }
    return sStream != NULL;
}

static int slot_of(int mask) {
    int i;

    for (i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            return i;
        }
    }
    return -1;
}

static void play(int mask, int id, int volume, int pan, int pitch, int handle) {
    int slot = slot_of(mask), k, pick = -1;
    uint32_t start, rate;
    double theta;
    Voice *v;

    if (slot < 0 || !sBanks[slot].set || !lookup(&sBanks[slot], id, &start, &rate)) {
        return;
    }
    for (k = 0; k < VOICES; k++) {
        if (!sVoices[k].on) {
            pick = k;
            break;
        }
    }
    if (pick < 0) { /* all busy: take one that is being stopped, else the first */
        for (k = 0; k < VOICES && !sVoices[k].stopping; k++) {
        }
        pick = k < VOICES ? k : 0;
    }
    v = &sVoices[pick];
    memset(v, 0, sizeof(*v));
    v->bank = slot;
    v->id = id;
    v->handle = handle;
    v->pos = start;
    v->step = (double)rate * pow(2.0, (double)pitch / 1200.0) / (double)OUT_RATE;
    v->frac = 0.0;
    v->fade = 1.0f;
    theta = (sMono ? 0.5 : (double)pan / 127.0) * 1.5707963267948966;
    v->gl = (float)(cos(theta) * 1.41421356) * ((float)volume / 127.0f) * sBanks[slot].volume * SE_GAIN;
    v->gr = (float)(sin(theta) * 1.41421356) * ((float)volume / 127.0f) * sBanks[slot].volume * SE_GAIN;
    v->on = 1;
    if (getenv("BT2_SND_VERBOSE") != NULL) {
        fprintf(stderr, "se: play bank %d effect %d: %u Hz, volume %d, pan %d, pitch %d, handle %d\n", slot, id, rate, volume, pan, pitch, handle);
    }
}

/* Stops voices: by bank mask (id < 0, handle < 0), by bank and number, or by handle. */
static void stop(int mask, int id, int handle) {
    int k;

    for (k = 0; k < VOICES; k++) {
        Voice *v = &sVoices[k];
        if (v->on && ((handle >= 0 && v->handle == handle) || (handle < 0 && (mask & (1 << v->bank)) && (id < 0 || v->id == id)))) {
            v->stopping = 1;
        }
    }
}

/* ------------------------------------------------------------ lo que llama el juego (funciones de Sony) */

static int sRpcLog = -1;

/* sceSifSetDma: memoria principal -> memoria del IOP. SifDmaData = { u32 data (EE), u32 addr (IOP), s32 size, s32 mode }. */
void Port_SifSetDma(uint32_t dp, int count) {
    const uint32_t *d = (const uint32_t *)(uintptr_t)dp;
    int i;
    if (sIop == NULL) { sIop = calloc(1, IOP_SIZE); }
    for (i = 0; sIop != NULL && d != NULL && i < count; i++) {
        uint32_t data = d[i * 4], addr = d[i * 4 + 1], size = d[i * 4 + 2];
        if (addr != 0 && data != 0 && (int32_t)size > 0 && addr < IOP_SIZE && size <= IOP_SIZE - addr) {
            memcpy(sIop + addr, (void *)(uintptr_t)data, size);
        }
    }
}

/* sceSdRemote: 0x80D0 = transfiere `size` bytes de la memoria del IOP a la del SPU2; 0x80F0 = terminada? (siempre: es inmediata).
   Args del juego: (core, modo, iopAddr, spuAddr, size). */
int Port_SdRemote(int cmd, uint32_t core, uint32_t mode, uint32_t iopAddr, uint32_t spuAddr, uint32_t size) {
    (void)core; (void)mode;
    if (cmd == 0x80D0) {
        const uint8_t *src = iop_ptr(iopAddr);
        if (sRpcLog < 0) { sRpcLog = getenv("BT2_SND_RPCLOG") != NULL; }
        if (sRpcLog) { fprintf(stderr, "snd: SPU upload iop=%x spu=%x size=%x\n", iopAddr, spuAddr, size); }
        if (src != NULL && spuAddr < SPU_SIZE && size <= SPU_SIZE - spuAddr && iopAddr + size <= IOP_SIZE) {
            if (sStream != NULL) { SDL_LockAudioStream(sStream); }
            memcpy(&sSpu[spuAddr], src, size);
            if (sStream != NULL) { SDL_UnlockAudioStream(sStream); }
        }
        return 0;
    }
    return cmd == 0x80F0 ? 1 : 0;
}

/* sceSifCallRpc a SOUNDS.IRX (servidor 0x2000004, el unico que llama el juego asi): una orden, respondida al instante.
   Protocolo de BT2 (distinto al de BT3; sacado de port/eq/297*.c y del despacho de SOUNDS.IRX, docs/AUDIO_PLAN.md):
     0x10 INIT {stereo, tam}           0x20 BANCO (apila) {spuAddr, hdIop, seqIop}  -> ranura = cuenta++
     0x30 DESAPILAR el ultimo banco    0x80 BANCO EN RANURA {spuAddr, hdIop, seqIop, ranura}
     0x40 COLA: byte n; banco[n] en +1, id en +0x21, volumen en +0x41, pan en +0x61, s16 pitch (cents) en +0x82
          el byte de banco: bajo 5 bits = ranura; 0x80 = reproducir recordando la voz; 0x40 = parar la voz recordada (banco, id)
     0x50 volumen/fundido (sin efecto)    0x60 ESTEREO {1 = estereo, 0 = mono}   0x70 VOLUMEN {0..127}
     0x100 RESET (para todo)           0x200 PARAR bancos {-, -, -, mascara} */
void Port_SndRpc(int fno, uint32_t sendp, int sendSize, uint32_t recvp, int recvSize) {
    const int32_t *w = (const int32_t *)(uintptr_t)sendp;
    void *recv = (void *)(uintptr_t)recvp;
    const uint8_t *q = (const uint8_t *)(uintptr_t)sendp;
    static int sCount;
    int ready = stream_ready(), i;

    (void)sendSize;
    if (sRpcLog < 0) { sRpcLog = getenv("BT2_SND_RPCLOG") != NULL; }
    if (sRpcLog && fno != 0x40) {
        fprintf(stderr, "snd: RPC fno=%x size=%d args=%d,%d,%d,%d\n", fno, sendSize, w ? w[0] : 0, w ? w[1] : 0, w ? w[2] : 0, w ? w[3] : 0);
    }
    if (recv != NULL && recvSize >= 4) {
        memset(recv, 0, 4); /* la palabra de resultado */
    }
    if (w == NULL) { return; }
    if (sStream != NULL) { SDL_LockAudioStream(sStream); }
    switch (fno) {
    case 0x10: /* INIT */
        break;
    case 0x20: /* BANCO apilado */
    case 0x80: { /* BANCO en la ranura w[3] */
        int slot = fno == 0x20 ? sCount : w[3];
        if (slot >= 0 && slot < 8) {
            sBanks[slot].set = 1;
            sBanks[slot].spu = (uint32_t)w[0];
            sBanks[slot].hd = iop_ptr((uint32_t)w[1]);
            sBanks[slot].sq = iop_ptr((uint32_t)w[2]);
            sBanks[slot].paused = 0;
            if (sBanks[slot].volume == 0.0f) { sBanks[slot].volume = 1.0f; }
            sCount = slot + 1;
            if (getenv("BT2_SND_VERBOSE") != NULL) { fprintf(stderr, "se: banco en ranura %d spu=%x hd=%x sq=%x\n", slot, w[0], w[1], w[2]); }
        }
        break;
    }
    case 0x30: /* desapilar */
        if (sCount > 0) {
            sCount--;
            sBanks[sCount & 7].set = 0;
            for (i = 0; i < VOICES; i++) { if (sVoices[i].on && sVoices[i].bank == (sCount & 7)) { sVoices[i].on = 0; } }
        }
        break;
    case 0x60: sMono = w[0] == 0; break;
    case 0x50: break; /* fundido de volumen por mascara de bancos {fade, -, -, mascara}: el juego solo lo manda al arrancar (0,0,0,0x1F) */
    case 0x70: /* VOLUMEN de todos los bancos */
        for (i = 0; i < 8; i++) { sBanks[i].volume = (float)w[0] / 127.0f; }
        break;
    case 0x100: /* RESET */
        for (i = 0; i < VOICES; i++) { sVoices[i].on = 0; }
        break;
    case 0x200: stop(w[3], -1, -1); break; /* PARAR bancos */
    case 0x40: { /* COLA */
        int n = q[0];
        for (i = 0; ready && i < n && i < 32; i++) {
            int bank = q[1 + i] & 0x1F, flags = q[1 + i] & 0xE0, id = q[0x21 + i];
            int vol = q[0x41 + i], pan = q[0x61 + i], pitch = (int16_t)le16(q + 0x82 + 2 * i);
            if (flags & 0x40) {
                stop(0, -1, 0x1000 | (bank << 8) | id);
            } else {
                play(1 << bank, id, vol, pan, pitch, (flags & 0x80) ? (0x1000 | (bank << 8) | id) : -1);
            }
        }
        break;
    }
    default: break;
    }
    if (sStream != NULL) { SDL_UnlockAudioStream(sStream); }
}
