/*
 * GS, DMA, vsync, pad, tarjeta de memoria, sonido y MPEG minimos del modo headless (etapa 4). Todo "hecho / inactivo":
 * los datos DMA se descartan, esperar un vsync cuenta un frame (gPortVBlanks). Un renderizador real (etapa 5) se engancha
 * en Port_DmaTransfer / Port_VBlank. Los argumentos se ignoran (u32: los punteros del juego son de 4 bytes).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef uint32_t u32;
typedef int32_t s32;

extern unsigned gPortVBlanks;
static u32 sVsyncHandler;
static long sMaxVBlanks = -1;

/* ---------------------------------------------------------------- GS */
void sceGsResetGraph(u32 a, u32 b, u32 c, u32 d) { (void)a; (void)b; (void)c; (void)d; }
void sceGsResetPath(void) {}
void sceGsSetDefClear(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; }
s32 sceGsSyncPath(u32 mode, u32 timeout) { (void)mode; (void)timeout; return 0; }
/* sceGsLoadImage (libgraph): GIF tag (A+D, 4 regs) + BITBLTBUF, TRXPOS, TRXREG, TRXDIR. Exec envia la cabecera y los pixeles
   (paquete IMAGE) por la ruta GIF, en trozos de hasta 0x7FFF quadwords. */
extern void Port_GsGifChannel(u32 addr, u32 qwc, int chain);
extern int Gs_PsmBits(u32 psm);
typedef struct { uint64_t tag[2]; uint64_t bitbltbuf, a0, trxpos, a1, trxreg, a2, trxdir, a3; } LoadImage;
static u32 sLoadBytes;
void sceGsSetDefLoadImage(u32 p, u32 dbp, u32 dbw, u32 dpsm, u32 x, u32 y, u32 w, u32 h) {
    LoadImage *l = (LoadImage *)(uintptr_t)p;
    l->tag[0] = 4ull | (1ull << 15) | (1ull << 60); l->tag[1] = 0xE;
    l->bitbltbuf = (uint64_t)(dbp & 0x3FFF) << 32 | (uint64_t)(dbw & 0x3F) << 48 | (uint64_t)(dpsm & 0x3F) << 56; l->a0 = 0x50;
    l->trxpos = (uint64_t)(x & 0x7FF) << 32 | (uint64_t)(y & 0x7FF) << 48; l->a1 = 0x51;
    l->trxreg = (uint64_t)(w & 0xFFF) | (uint64_t)(h & 0xFFF) << 32; l->a2 = 0x52;
    l->trxdir = 0; l->a3 = 0x53;
    sLoadBytes = (uint32_t)(((uint64_t)w * h * (uint32_t)Gs_PsmBits(dpsm) + 7) / 8);
}
s32 sceGsExecLoadImage(u32 p, u32 src) {
    LoadImage *l = (LoadImage *)(uintptr_t)p;
    uint32_t w = (uint32_t)(l->trxreg & 0xFFF), h = (uint32_t)((l->trxreg >> 32) & 0xFFF), psm = (uint32_t)(l->bitbltbuf >> 56) & 0x3F;
    uint32_t qw = (uint32_t)(((uint64_t)w * h * (uint32_t)Gs_PsmBits(psm) + 127) / 128);
    static uint64_t tag[2] __attribute__((aligned(16)));
    Port_GsGifChannel(p, 5, 0);
    while (qw) {
        uint32_t n = qw > 0x7FFF ? 0x7FFF : qw;
        tag[0] = (uint64_t)n | (1ull << 15) | (2ull << 58); tag[1] = 0;
        Port_GsGifChannel((u32)(uintptr_t)tag, 1, 0);
        Port_GsGifChannel(src, n, 0);
        src += n * 16; qw -= n;
    }
    return 0;
}

/* sceGsSetDefStoreImage / sceGsExecStoreImage (libgraph): lectura de VRAM a memoria (la usa func_0027A448, captura de
   pantalla). Sin lectura de VRAM todavia: no-op (el buffer destino queda como estaba). */
void sceGsSetDefStoreImage(u32 p, u32 sbp, u32 sbw, u32 spsm, u32 x, u32 y, u32 w, u32 h) { (void)p; (void)sbp; (void)sbw; (void)spsm; (void)x; (void)y; (void)w; (void)h; }
s32 sceGsExecStoreImage(u32 p, u32 dst) { (void)p; (void)dst; return 0; }

u32 sceGsSyncVCallback(u32 handler) { u32 old = sVsyncHandler; sVsyncHandler = handler; return old; }

/* Un vsync: corre el handler como la interrupcion. Con ventana (BT2_GS=gpu) el vsync es el reloj: uno cada 1/59.94 s
   (el juego espera uno por cuadro en menus y dos en combate). Sin ventana no se espera tiempo real (BT2_PACED=1 lo
   fuerza). BT2_MAXFRAMES=n corta el programa con un informe despues de n vsyncs. */
extern int GsGpu_Enabled(void);
unsigned long long gPortSleptNs;   /* tiempo esperando aqui (la medicion de cuadros de gs_core.c lo resta) */
static unsigned long long now_ns(void) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (unsigned long long)ts.tv_sec * 1000000000ull + (unsigned long long)ts.tv_nsec; }
static unsigned long long sPerFight, sPerMenu;
static int sPerInit;
extern int Port_EnPelea(void);   /* plat_fightlog.c: 1 con la lista de los dos luchadores montada */
static unsigned long long period_hz(double hz) { return hz >= 1.0 ? (unsigned long long)(1e9 / hz) : 16683350ull; }
static unsigned long long vblank_period(void) {
    if (!sPerInit) {   /* BT2_FPS=n: ritmo de vsync de los dos; BT2_FPS_FIGHT / BT2_FPS_MENU lo separan */
        const char *a = getenv("BT2_FPS"), *f = getenv("BT2_FPS_FIGHT"), *m = getenv("BT2_FPS_MENU");
        double ha = a ? atof(a) : 0.0, hf = f ? atof(f) : 0.0, hm = m ? atof(m) : 0.0;
        sPerInit = 1;
        if (hf < 1.0) hf = ha >= 1.0 ? ha : 59.94;
        if (hm < 1.0) hm = ha >= 1.0 ? ha : 59.94;
        sPerFight = period_hz(hf);
        sPerMenu = period_hz(hm);
        if (f != NULL || m != NULL || getenv("BT2_FPSLOG") != NULL) {
            fprintf(stderr, "bt2: ritmo: pelea %.2f Hz (%llu ns), menu %.2f Hz (%llu ns)%s\n",
                    hf, sPerFight, hm, sPerMenu, sPerFight == sPerMenu ? " (iguales: sync)" : "");
        }
    }
    /* La pelea 3D y los menus pueden pedir distinto numero de vblanks por cuadro; el intervalo se elige por
       fase. vblank_wait() sigue con su grilla libre y se reajusta sola cuando cambia el periodo. */
    return Port_EnPelea() ? sPerFight : sPerMenu;
}
static void vblank_wait(void) {
    static unsigned long long next;
    unsigned long long per = vblank_period();
    unsigned long long t = now_ns();
    /* Un vblank por llamada sobre una grilla libre: si el cuadro se pasó, se pierden los flancos que ya
       pasaron (como en la PS2, que no recupera tiempo) en vez de correr cuadros de más para "recuperar" el
       atraso. Antes, cuando el cuadro tardaba más de un período no dormía y acumulaba deuda, y después corría
       en ráfaga (medido: ventanas de 130-222 cuadros/s); eso daba 56.8 Hz sostenidos en pelea y tirones. */
    if (next == 0) next = t;
    do { next += per; } while (next <= t);
    {
        struct timespec ts = {0, (long)(next - t)};
        nanosleep(&ts, NULL);
        gPortSleptNs += now_ns() - t;
    }
}
void Port_VBlank(void) {
    {   /* B25 (herramienta): arma el watchpoint de float (BT2_WATCH_F32) al llegar al vblank BT2_WATCH_FROM */
        static int armed;
        extern void bt2_watch_f32_from_env(void);
        if (!armed && getenv("BT2_WATCH_F32") != NULL &&
            gPortVBlanks >= (unsigned)(getenv("BT2_WATCH_FROM") ? atoi(getenv("BT2_WATCH_FROM")) : 1)) {
            armed = 1;
            bt2_watch_f32_from_env();
        }
    }
    static int paced = -1;
    if (paced < 0) paced = getenv("BT2_PACED") != NULL;
    if ((GsGpu_Enabled() || paced) && !getenv("BT2_UNCAPPED")) vblank_wait();
    gPortVBlanks++;
    { extern void bt2_fightlog_frame(void); bt2_fightlog_frame(); }   /* BT2_FIGHTLOG=1: port/full/plat_fightlog.c */
    { extern void bt2_statelog_frame(void); bt2_statelog_frame(); }   /* log por estado: port/full/plat_fightlog.c */
    {   /* BT2_FPSLOG=1: cada 60 vsyncs imprime el ritmo real (vsyncs/s y cuadros del renderer/s) con la hora: sirve para correlacionar
           saltos de fps con el video de jugar.sh (el reloj del log y el del video parten del mismo arranque) */
        static int on = -1;
        static unsigned long long t0, tl;
        static unsigned vl, gl;
        extern unsigned gGsFrame;
        if (on < 0) on = getenv("BT2_FPSLOG") != NULL;
        if (on) {
            unsigned long long t = now_ns();
            if (t0 == 0) { t0 = tl = t; }
            if (gPortVBlanks % 60 == 0) {
                double dt = (double)(t - tl) / 1e9;
                fprintf(stderr, "fpslog: t=%.1fs vsync=%u vsync/s=%.1f gsframe/s=%.1f\n", (double)(t - t0) / 1e9, gPortVBlanks,
                        (gPortVBlanks - vl) / dt, (gGsFrame - gl) / dt);
                tl = t; vl = gPortVBlanks; gl = gGsFrame;
            }
        }
    }
    if (sMaxVBlanks < 0) { const char *e = getenv("BT2_MAXFRAMES"); sMaxVBlanks = e ? atol(e) : 0; }
    if (sMaxVBlanks > 0 && (long)gPortVBlanks >= sMaxVBlanks) {
        fprintf(stderr, "bt2full: %u vsyncs contados (BT2_MAXFRAMES): fin\n", gPortVBlanks);
        exit(0);
    }
    { extern void Port_DemoTick(void); Port_DemoTick(); }   /* plat_demo.c: BT2_DEMO=1 */
    if (sVsyncHandler) ((s32 (*)(s32))(uintptr_t)sVsyncHandler)(0);
}
s32 sceGsSyncV(u32 mode) { (void)mode; Port_VBlank(); return 0; }

/* Tope en el present del renderer: las pantallas que no llaman a sceGsSyncV (la seleccion de mapa/musica) se
 * dibujaban a la velocidad del CPU (medido: 367 cuadros/s). Si el cuadro llega antes de la grilla, se espera el
 * flanco; si llega tarde, no se recupera despues (igual que la PS2). No hace nada sin GPU ni con BT2_UNCAPPED. */
void Port_PacePresent(void) {
    static int paced = -1;
    static unsigned long long last;
    unsigned long long per, t;

    if (paced < 0) paced = getenv("BT2_PACED") != NULL;
    if (getenv("BT2_UNCAPPED") || !(GsGpu_Enabled() || paced)) { last = 0; return; }
    per = vblank_period();
    t = now_ns();
    if (last == 0) { last = t; return; }
    if (t - last < per * 3 / 4) {
        unsigned long long target = last + per;
        struct timespec ts = {0, (long)(target - t)};
        nanosleep(&ts, NULL);
        gPortSleptNs += now_ns() - t;
        last = target;
    } else {
        last = t;
    }
}

/* ---------------------------------------------------------------- DMA (sceDma*) : completado inmediato */
void WaitDma(u32 a) { (void)a; }

/* ---------------------------------------------------------------- pad (DualShock 2: nada pulsado) */
s32 sceDbcInit(void) { return 1; }
s32 scePad2Init(u32 a) { (void)a; return 1; }
static int sPadSockets;
s32 scePad2CreateSocket(u32 a, u32 b) { (void)a; (void)b; return sPadSockets++; }
s32 scePad2GetState(u32 s) { (void)s; return 1; }          /* conectado y listo */
s32 scePad2GetButtonProfile(u32 s, u32 profile) {
    unsigned char *p = (unsigned char *)(uintptr_t)profile; (void)s;
    if (p) { p[0] = 0xFF; p[1] = 0xFF; p[2] = 0xFF; p[3] = 0x03; }
    return 4;
}
extern int Port_PadRead(int socket, unsigned char *data);   /* gs_input.c: teclado y mandos (solo con ventana) */
s32 scePad2Read(u32 s, u32 data) {                          /* botones activos en bajo, palancas en reposo 0x80 */
    unsigned char *d = (unsigned char *)(uintptr_t)data; int i;
    if (!d) return 0;
    if (Port_PadRead((int)s, d)) { static unsigned short sPadLast[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}; extern unsigned gPortVBlanks; if (getenv("BT2_PADLOG") && (unsigned short)(d[0] << 8 | d[1]) != sPadLast[s & 3]) fprintf(stderr, "pad %u vblank %u: %02X%02X newmask=%X mcstate=%d\n", s, gPortVBlanks, d[0], d[1], *(u32 *)0x3B0C34, (*(u32 *)0x421C00 ? *(s32 *)(uintptr_t)(*(u32 *)0x421C00 + 0x24) : -1)); sPadLast[s & 3] = (unsigned short)(d[0] << 8 | d[1]); return 18; } /* 0x421C00 is 0 outside the memcard task (crash with PADLOG after a UB loss) */
    d[0] = 0xFF; d[1] = 0xFF;
    for (i = 2; i < 6; i++) d[i] = 0x80;
    for (i = 6; i < 18; i++) d[i] = 0;
    return 18;
}
s32 sceVibSetActParam(u32 a, u32 b, u32 c, u32 d) { (void)a; (void)b; (void)c; (void)d; return 0; }

/* ---------------------------------------------------------------- sonido (libsd por RPC), MPEG: inactivos */
s32 sceSdRemoteInit(void) { return 0; }
s32 sceSdRemoteCallbackInit(u32 a) { (void)a; return 0; }

/* ---------------------------------------------------------------- registros de canales DMA
   En la PS2 el juego inicia una transferencia con el bit 0x100 de Dn_CHCR y el hardware lo baja al terminar. Aqui
   include/sys/dma.h (bajo PORT) hace pasar D1_CHCR / D2_CHCR por Port_DmaChcr: la transferencia pendiente "se completa"
   (datos descartados en headless) y el bit baja, asi que los bucles "esperar canal libre" terminan. */
#define REG(a) ((volatile u32 *)(uintptr_t)(a))
unsigned long gPortDmaStarts[16];
extern void Port_GsVif1Chain(u32 tadr, int tte);
extern void Port_GsGifChannel(u32 addr, u32 qwc, int chain);
/* Canal 1 = VIF1 (modelos por los microprogramas VU1; en modo cadena es la lista del cuadro), 2 = GIF (paquetes GS),
   4 = IPU (peliculas). gs_core.c los ejecuta (software o GPU) o los descarta (BT2_GS=none). */
extern u32 full_dma_addr(u32 a);
static void Port_DmaTransfer(s32 channel) {
    if (channel == 1 && ((*REG(0x10009000u) >> 2) & 3) == 1) Port_GsVif1Chain(full_dma_addr(*REG(0x10009030u)), (int)((*REG(0x10009000u) >> 6) & 1));
    if (channel == 2) {
        int chain = ((*REG(0x1000A000u) >> 2) & 3) == 1;
        Port_GsGifChannel(full_dma_addr(chain ? *REG(0x1000A030u) : *REG(0x1000A010u)), *REG(0x1000A020u), chain);
    }
}
volatile u32 *Port_DmaChcr(s32 channel) {
    volatile u32 *chcr = REG(0x10008000u + 0x1000u * (u32)channel - (channel == 4 ? 0xC00u : 0u));
    if (*chcr & 0x100u) { gPortDmaStarts[channel & 15]++; Port_DmaTransfer(channel); *chcr &= ~0x100u; }
    return chcr;
}
/* sceSdRemote(rpc, cmd, ...): libsd por RPC. 0x80F0 = rSdVoiceTransStatus: 1 = la transferencia a la SPU ya termino (sin sonido: siempre). */
extern s32 Port_SdRemote(s32 cmd, u32 a, u32 b, u32 c, u32 d, u32 e);   /* plat_snd_se.c: 0x80D0 = IOP -> SPU, 0x80F0 = estado */
s32 sceSdRemote(s32 rpc, s32 cmd, u32 a, u32 b, u32 c, u32 d, u32 e) { (void)rpc; return Port_SdRemote(cmd, a, b, c, d, e); }

/* ---------------------------------------------------------------- huecos que el renderer pide a la capa del port
   (el sonido de BT2 esta en plat_snd_adx.c / plat_snd_se.c) */
int gPortMusicPercent = 100, gPortSePercent = 100;
int gPortMenuMode;                       /* 1 = menus: sin ensanchado de pantalla; el juego aun no lo marca */
volatile u32 gPortDataStripped;

/* ---- forma de la imagen (ancho/alto x 1000; 1333 = 4:3). BT2_ASPECT=16:9, BT2_WIDE=1/0, BT2_WINDOW=WxH. Solo el renderer la
   usa por ahora: el C del juego aun no ensancha la proyeccion (Port_WideFactor de BT3), asi que ancho = barras / estirado. */
extern int Port_Setting(const char *name, int def);
static int sAspectMilli = -1;
int Port_AspectMilli(void) {
    if (sAspectMilli < 0) {
        int a = 0, b = 0, w = 0, h = 0;
        /* F2: 16:9 por defecto (1778 = 16/9*1000). BT2_WIDE=0 o BT2_ASPECT=4:3 vuelven a 4:3; la UI (F1) lo pisa
           y queda guardado en bt2_settings.txt. */
        sAspectMilli = Port_Setting("aspect_milli", 1778);
        if (getenv("BT2_WIDE") && atoi(getenv("BT2_WIDE")) == 0) sAspectMilli = 1333;
        else if (getenv("BT2_ASPECT") && sscanf(getenv("BT2_ASPECT"), "%d:%d", &a, &b) == 2 && a > 0 && b > 0) sAspectMilli = a * 1000 / b;
        else if (getenv("BT2_WIDE")) sAspectMilli = 1778;
        else if (getenv("BT2_WINDOW") && sscanf(getenv("BT2_WINDOW"), "%dx%d", &w, &h) == 2 && h > 0 && w * 2 > h * 3) sAspectMilli = w * 1000 / h;
        if (sAspectMilli < 1333) sAspectMilli = 1333;
        if (sAspectMilli > 4000) sAspectMilli = 4000;
    }
    return sAspectMilli;
}
void Port_SetAspectMilli(int m) { sAspectMilli = m < 1333 ? 1333 : m > 4000 ? 4000 : m; }
int Port_IsWide(void) { return Port_AspectMilli() > 1340; }

/* ventana de ajustes (ui.cpp): pestana "Unlock everything" de BT3; en BT2 aun no hace nada */
volatile int gPortUnlockAll, gPortUnlockDone;
