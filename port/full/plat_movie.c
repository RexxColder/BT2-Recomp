/*
 * Peliculas SFD (logos, opening, ending) por HLE: sustituye los mwPly* de CRI Sofdec que usa func_0024BA78(name)
 * (port/eq/24BA78.c) sin emular IOP/IPU. Se demuxa el MPEG-PS (.SFD) y se decodifica el video con libavcodec; el juego
 * hace el resto (sube el cuadro a VRAM con sceGsExecLoadImage y lo pinta con su fundido), asi que aqui solo se cumple el
 * contrato del reproductor:
 *   mwPlySetFile/Start(ply, name)  abre ../DATA/<name>.SFD (BT2_DATA o gamedata, como plat_file.c) y arranca el reloj
 *   mwPlyGetFrame(ply, out)        out[0] = puntero al cuadro (0 = no hay cuadro nuevo), out+0xC = ancho, out+0x10 = alto.
 *                                  El cuadro es RGBA (A=0x80) en tiras de 16 pixeles de ancho: tira i en +i*alto*64 bytes
 *                                  (func_0024B980 lo sube con una LoadImage por tira).
 *   mwPlyGetStat(ply)              1 = preparando, 2 = reproduciendo, 3 = fin (4 = error; el juego trata 3 y 4 como fin)
 *   mwPlyFrameDone(ply)            el juego ya consumio el cuadro
 * El ritmo es el real de la pelicula (reloj de pared desde Start, 29.97 fps); saltar con Start/Cross lo hace el propio
 * juego (func_0024BA78 comprueba D_003B0B00+0x134 & 8), aqui no se duplica.
 * Variables: BT2_SKIP_MOVIES=1 (terminan al instante), BT2_MOVIELOG=1.
 *
 * B15 (preview del Map Select): ademas de los SFD sueltos, el juego reproduce videos que viven DENTRO de un AFS
 *   (ZS2US_1.AFS, ptid/flid). func_002BB038 (mwPlyStartAfsLp) llama a Port_MovieStartAfs(ptid, flid); aqui se lee el
 *   bloque del AFS a memoria (plat_file.c: Port_ReadAudioFile), se demuxa/decodifica desde memoria con un AVIOContext
 *   propio y se rebobina al llegar al final (loop). Esos videos responden GetStat = 2 en cuanto estan abiertos: el juego
 *   consulta el estado ANTES de pedir cuadro en esa rama.
 *
 * AUDIO: el demuxer entrega los paquetes de los streams que no son video (el ADX, stream 0xC0 del SFD) a
 *   void Movie_AudioPacket(const uint8_t *adx, int len, int64_t pts)   (pts en unidades de 1/90000 s desde el inicio)
 * Es una funcion DEBIL vacia: quien implemente el sonido (port/full/gs/snd_adx.c) la define de forma fuerte. Tambien hay
 *   void Movie_AudioBegin(int sample_rate, int channels) / void Movie_AudioEnd(void)  (debiles) al abrir/cerrar la pelicula.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/mman.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

typedef uint32_t u32;
typedef int32_t s32;

__attribute__((weak)) void Movie_AudioPacket(const uint8_t *adx, int len, int64_t pts) { (void)adx; (void)len; (void)pts; }
__attribute__((weak)) void Movie_AudioBegin(int sample_rate, int channels) { (void)sample_rate; (void)channels; }
__attribute__((weak)) void Movie_AudioEnd(void) {}

#define MW 512
#define MH 448

/* Lector AVIO en memoria: el bloque del AFS ya esta entero en RAM (ver Port_MovieStartAfs). */
typedef struct { const uint8_t *p; size_t n, pos; } MemIO;
static int mem_read(void *op, uint8_t *buf, int n) {
    MemIO *m = op;
    size_t left;
    /* EOF explicito: devolver 0 hace que libavformat reintente para siempre (avformat_find_stream_info en bucle) */
    if (m->pos >= m->n) return AVERROR_EOF;
    left = m->n - m->pos;
    if (left < (size_t)n) n = (int)left;
    memcpy(buf, m->p + m->pos, n);
    m->pos += n;
    return n;
}
static int64_t mem_seek(void *op, int64_t off, int whence) {
    MemIO *m = op;
    if (whence == AVSEEK_SIZE) return (int64_t)m->n;
    if (whence == SEEK_CUR) off += (int64_t)m->pos;
    else if (whence == SEEK_END) off += (int64_t)m->n;
    if (off < 0 || (size_t)off > m->n) return -1;
    m->pos = (size_t)off;
    return off;
}

static struct {
    AVFormatContext *fmt; AVCodecContext *cod; struct SwsContext *sws; AVPacket *pkt; AVFrame *frm;
    int vstream, open, eof, drained, started, frames, shown;
    int64_t t0;          /* ns del reloj al llegar el primer cuadro pedido */
    double fps; int64_t first_pts;
    uint8_t *strips;     /* cuadro en tiras, direccion de 32 bits (el juego la usa como puntero PS2) */
    int pending;         /* hay un cuadro decodificado esperando su hora */
    int w, h;            /* ancho/alto actuales del cuadro (default 512x448; los videos del AFS son 512x256) */
    int loop;            /* 1 = pelicula del AFS: rebobina al terminar */
    int live;            /* 1 = pelicula del AFS: GetStat responde 2 en cuanto esta abierta */
    AVIOContext *pb;     /* AVIO propio cuando la pelicula viene de memoria (AFS) */
    MemIO *io;
    uint8_t *afsData;    /* bloque del AFS en RAM; lo libera start_afs al reemplazarlo */
    u32 afsSize;
    int afsPtid, afsFlid;
} M;

static int64_t now_ns(void) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (int64_t)ts.tv_sec * 1000000000ll + ts.tv_nsec; }
static int logon(void) { static int l = -1; if (l < 0) l = getenv("BT2_MOVIELOG") != NULL; return l; }

/* libera el AVIO propio (solo cuando la pelicula vino de memoria) */
static void close_io(void) {
    av_freep(&M.pb->buffer);
    avio_context_free(&M.pb);
    free(M.io); M.io = NULL;
}

static void close_movie(void) {
    if (!M.open) return;
    if (logon()) fprintf(stderr, "[movie] fin: %d cuadros decodificados, %d mostrados\n", M.frames, M.shown);
    Movie_AudioEnd();
    sws_freeContext(M.sws); av_frame_free(&M.frm); av_packet_free(&M.pkt);
    avcodec_free_context(&M.cod); avformat_close_input(&M.fmt);
    M.sws = NULL; M.open = 0;
    if (M.pb) close_io();          /* M.afsData NO se libera: lo reusa/libera start_afs */
    M.live = M.loop = 0;
}

/* Decoder, strips, fps, flags y audio sobre M.fmt ya abierto. w/h = tamano al que se escala el cuadro. */
static int movie_init(const char *label, int w, int h, int loop, int live) {
    int i;
    M.w = w; M.h = h; M.loop = loop; M.live = live;
    M.vstream = av_find_best_stream(M.fmt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (M.vstream < 0) return 0;
    const AVCodecParameters *par = M.fmt->streams[M.vstream]->codecpar;
    const AVCodec *dec = avcodec_find_decoder(par->codec_id);
    M.cod = dec ? avcodec_alloc_context3(dec) : NULL;
    if (!M.cod || avcodec_parameters_to_context(M.cod, par) < 0 || avcodec_open2(M.cod, dec, NULL) < 0) return 0;
    M.pkt = av_packet_alloc(); M.frm = av_frame_alloc();
    if (!M.strips) M.strips = mmap(NULL, MW * MH * 4, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
    if (M.strips == MAP_FAILED) { M.strips = NULL; return 0; }
    AVRational r = M.fmt->streams[M.vstream]->avg_frame_rate;
    M.fps = r.num > 0 && r.den > 0 ? (double)r.num / r.den : 29.97;
    M.open = 1; M.eof = M.drained = M.started = M.frames = M.shown = M.pending = 0; M.first_pts = AV_NOPTS_VALUE;
    for (i = 0; i < (int)M.fmt->nb_streams; i++) {
        const AVCodecParameters *a = M.fmt->streams[i]->codecpar;
        if (a->codec_type == AVMEDIA_TYPE_AUDIO) { Movie_AudioBegin(a->sample_rate, a->ch_layout.nb_channels); break; }
    }
    if (logon()) fprintf(stderr, "[movie] %s %dx%d (escalado a %dx%d, loop %d) %.2f fps\n", label, par->width, par->height, w, h, loop, M.fps);
    return 1;
}

static int open_movie(const char *name) {
    char base[96], path[512]; const char *root = getenv("BT2_DATA"), *p, *b = name;
    size_t n = 0; int i;
    M.w = MW; M.h = MH; M.loop = 0; M.live = 0;
    for (p = name; *p; p++) if (*p == '/' || *p == '\\') b = p + 1;
    for (p = b; *p && *p != ';' && n < sizeof(base) - 1; p++) base[n++] = *p;
    base[n] = 0;
    for (i = 0; i < 2; i++) {
        if (i) for (n = 0; base[n]; n++) base[n] = (char)toupper((unsigned char)base[n]);
        snprintf(path, sizeof path, "%s/DATA/%s", root ? root : "gamedata", base);
        if (avformat_open_input(&M.fmt, path, NULL, NULL) == 0) break;
        M.fmt = NULL;
    }
    if (!M.fmt || avformat_find_stream_info(M.fmt, NULL) < 0) { fprintf(stderr, "[movie] no se puede abrir %s\n", name); return 0; }
    return movie_init(path, MW, MH, 0, 0);
}

/* Abre la pelicula que ya esta en M.afsData (bloque del AFS) desde memoria, en bucle. 0 si no se pudo. */
static int open_afs_movie(void) {
    if (!M.afsData || !M.afsSize) return 0;
    M.io = calloc(1, sizeof *M.io);
    if (!M.io) return 0;
    M.io->p = M.afsData; M.io->n = M.afsSize;
    M.pb = avio_alloc_context(av_malloc(4096), 4096, 0, M.io, mem_read, NULL, mem_seek);
    M.fmt = avformat_alloc_context();
    if (!M.pb || !M.fmt) { fprintf(stderr, "[movie] AFS: sin memoria para el AVIO\n"); return 0; }
    M.fmt->pb = M.pb;
    /* el AVIO es nuestro: que avformat_close_input no lo libere */
    M.fmt->flags |= AVFMT_FLAG_CUSTOM_IO;
    if (avformat_open_input(&M.fmt, "afs", NULL, NULL) < 0 || avformat_find_stream_info(M.fmt, NULL) < 0) {
        fprintf(stderr, "[movie] AFS: no se pudo abrir el stream\n");
        return 0;
    }
    M.fmt->flags |= AVFMT_FLAG_CUSTOM_IO;
    return movie_init("afs", 512, 256, 1, 1);   /* ancho/alto medidos del mpeg2video del ZS2US_1.AFS */
}

/* decodifica el siguiente cuadro a M.strips; 0 al final */
static int next_frame(void) {
    for (;;) {
        int got = avcodec_receive_frame(M.cod, M.frm);
        if (got == 0) {
            if (M.first_pts == AV_NOPTS_VALUE) M.first_pts = M.frm->pts != AV_NOPTS_VALUE ? M.frm->pts : 0;
            M.sws = sws_getCachedContext(M.sws, M.frm->width, M.frm->height, M.frm->format, M.w, M.h, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);
            static uint8_t rgba[MW * MH * 4];
            uint8_t *dst[1] = {rgba}; int ds[1] = {M.w * 4};
            sws_scale(M.sws, (const uint8_t *const *)M.frm->data, M.frm->linesize, 0, M.frm->height, dst, ds);
            for (int s = 0; s < M.w / 16; s++)
                for (int y = 0; y < M.h; y++) {
                    uint8_t *d = M.strips + ((size_t)s * M.h + y) * 64; const uint8_t *q = rgba + (size_t)y * M.w * 4 + s * 64;
                    memcpy(d, q, 64);
                    for (int x = 3; x < 64; x += 4) d[x] = 0x80;
                }
            M.frames++;
            return 1;
        }
        if (got == AVERROR_EOF) return 0;
        if (M.eof) { avcodec_send_packet(M.cod, NULL); continue; }
        if (av_read_frame(M.fmt, M.pkt) < 0) {
            if (M.loop && M.pb) {   /* pelicula del AFS: rebobina sin cerrar */
                M.io->pos = 0;
                avio_seek(M.pb, 0, SEEK_SET);
                avformat_flush(M.fmt);
                avcodec_flush_buffers(M.cod);
                M.eof = 0; M.drained = 0; M.first_pts = AV_NOPTS_VALUE;
                continue;
            }
            M.eof = 1; avcodec_send_packet(M.cod, NULL); continue;
        }
        if (M.pkt->stream_index == M.vstream) avcodec_send_packet(M.cod, M.pkt);
        else {
            AVRational tb = M.fmt->streams[M.pkt->stream_index]->time_base;
            int64_t pts = M.pkt->pts == AV_NOPTS_VALUE ? -1 : av_rescale_q(M.pkt->pts, tb, (AVRational){1, 90000});
            if (M.fmt->streams[M.pkt->stream_index]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) Movie_AudioPacket(M.pkt->data, M.pkt->size, pts);
        }
        av_packet_unref(M.pkt);
    }
}

/* ---- mwPly* (direcciones PS2 del juego; ver plat_sdk.c para la version anterior en stubs) ---- */
static unsigned char sPly[0x400] __attribute__((aligned(16)));
void func_002B6208(u32 cfg) { (void)cfg; }
s32 func_002B30E0(u32 cfg) { (void)cfg; return 0x100; }
u32 func_002B4038(u32 cfg) { (void)cfg; return (u32)(uintptr_t)sPly; }
void func_002B88C0(u32 p, u32 q) { (void)p; (void)q; }
void func_002B6E50(u32 p, s32 file) {   /* mwPlyStart(ply, name) */
    (void)p;
    close_movie();
    if (getenv("BT2_SKIP_MOVIES") || !file || !open_movie((const char *)(uintptr_t)(u32)file)) { M.open = 1; close_movie(); }
}
void func_002B7BD8(void) {}

/* B15: preview del Map Select = pelicula dentro del AFS (mwPlyStartAfsLp). Se lee el bloque a RAM y se abre YA: el juego
   elige la rama live (418CC8, la unica que pide cuadro) mirando GetStat, asi que la pelicula tiene que estar abierta antes.
   Abrir no decodifica: el primer next_frame() ocurre en el primer func_002B4FD0. */
extern uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, u32 *outSize); /* port/full/plat_file.c */
static void start_afs(s32 ptid, s32 flid) {
    close_movie();
    free(M.afsData); M.afsData = NULL; M.afsSize = 0; M.afsPtid = ptid; M.afsFlid = flid;
    M.afsData = Port_ReadAudioFile(ptid, flid, NULL, &M.afsSize);
    if (M.afsData) fprintf(stderr, "[movie] AFS ptid %d flid 0x%X -> %u bytes\n", ptid, flid, M.afsSize);
    else fprintf(stderr, "[movie] AFS ptid %d flid 0x%X: no se pudo leer\n", ptid, flid);
    if (!M.afsData) return;
    if (!open_afs_movie()) {
        avformat_close_input(&M.fmt);
        if (M.pb) close_io();
        return;
    }
}
void Port_MovieStartAfs(s32 ptid, s32 flid) { start_afs(ptid, flid); }

/* El juego dibuja el cuadro y el fundido por el canal GIF (sceDmaSend(chan 2)): el renderer presenta un cuadro solo al
   terminar una cadena VIF1 (Port_GsVif1Chain). Se presenta aqui con una cadena vacia (un tag END) al final de cada pasada
   del bucle del juego en la que pidio cuadro (GetFrame), que es cuando dibuja. */
extern void Port_GsVif1Chain(u32 tadr, int tte);
static u32 sEndTag[4] __attribute__((aligned(16))) = {0x70000000u, 0, 0, 0};
static int sPresent;

void func_002B4FD0(u32 p, u32 out_) {   /* mwPlyGetFrame(ply, out) */
    u32 *out = (u32 *)(uintptr_t)out_; (void)p;
    memset(out, 0, 0x20);
    if (!M.open) return;
    sPresent = 1;
    /* avanza la decodificacion hasta el cuadro que toca por el reloj; el ultimo cuadro se entrega siempre (el juego lo sube
       a VRAM en cada pasada y presenta), asi no hay cuadros en negro entre dos de la pelicula */
    if (!M.drained) {
        int guard = 0;   /* tope: si el reloj salta, no decodificar sin fin en una sola pasada */
        if (!M.started && M.frames == 0) { if (!next_frame()) M.drained = 1; }
        if (!M.started) { M.started = 1; M.t0 = now_ns(); }
        while (!M.drained && guard++ < 64 && now_ns() - M.t0 >= (int64_t)(1e9 * M.frames / M.fps))
            if (!next_frame()) M.drained = 1;
    }
    if (M.frames == 0) return;
    out[0] = (u32)(uintptr_t)M.strips; out[3] = (u32)M.w; out[4] = (u32)M.h;
    if (M.shown++ % 100 == 0 && logon()) fprintf(stderr, "[movie] pasada %d, cuadro %d t=%.1fs\n", M.shown, M.frames, (now_ns() - M.t0) / 1e9);
}
void func_002B58F0(u32 p) { (void)p; }
s32 func_002B8328(u32 p) {   /* mwPlyGetStat */
    (void)p;
    if (sPresent) {
        /* ritmo de 60 Hz: el bucle del juego gira sin esperar al vsync mientras suena la pelicula (sin esto presentaba cientos de
           cuadros por segundo: CPU/GPU al 100 % y el contador de fps del renderer disparado) */
        static int64_t last;
        int64_t t = now_ns();
        if (last != 0 && t - last < 16683350ll) {
            struct timespec ts = {0, (long)(16683350ll - (t - last))};
            nanosleep(&ts, NULL);
            t = now_ns();
        }
        last = t;
        sPresent = 0;
        Port_GsVif1Chain((u32)(uintptr_t)sEndTag, 0);
    }
    if (M.open && M.live) return 2;   /* pelicula del AFS: ya esta decodificando (el juego pregunta antes de pedir cuadro) */
    if (!M.open || (M.drained && M.shown > 0)) return 3;
    return M.started ? 2 : 1;
}
void func_002B45D8(u32 p) { (void)p; close_movie(); }
void func_002B65C0(void) {}
