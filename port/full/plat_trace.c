/* Ultra logging del port (2026-10-23). Dos piezas:
 *
 *  1. BT2_ULTRALOG=1 enciende de una vez todos los logs que ya existen (BT2_SYSLOG, BT2_FILELOG, BT2_MC_LOG,
 *     BT3_TEX_LOG, BT2_DEMO_LOG, BT3_GS_VERBOSE) y la traza de llamadas. Lo que el usuario ya fijo a mano se respeta.
 *
 *  2. Traza de llamadas del codigo del juego. Solo existe en un build con instrumentacion
 *     (BT2_TRACE_BUILD=1 en build_full.py y link_full.py: clang -finstrument-functions, directorios aparte
 *     port/build/gen/full_trace y port/build/full_trace). Cada funcion del juego llama a __cyg_profile_func_enter/exit;
 *     aqui van a un anillo de eventos {vblank, funcion, llamador, profundidad} y a una tabla de "primera llamada".
 *
 *  Variables (la traza se activa con BT2_TRACE=1 o BT2_ULTRALOG=1):
 *     BT2_TRACE_FROM=N    empieza a grabar en el vblank N (def. 0)
 *     BT2_TRACE_TO=N      deja de grabar en el vblank N (def. nunca)
 *     BT2_TRACE_RING=N    eventos del anillo, se redondea a potencia de 2 (def. 4194304 = 64 MB)
 *     BT2_TRACE_OUT=ruta  base del volcado (def. /tmp/bt2_trace): escribe <ruta>.bin; scripts/trace_sym.py lo pasa a texto
 *  Volcado: SIGUSR1, al salir, y en un crash (on_segv de mem.c llama a bt2_trace_dump). */
#define _GNU_SOURCE
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned gPortVBlanks;

typedef struct { uint32_t frame, fn, caller; int32_t depth; } TraceEv;

static int sOn;                       /* grabando ahora */
static int sArmed;                    /* BT2_TRACE pedido */
static unsigned sFrom, sTo = 0xFFFFFFFFu;
static TraceEv *sRing;
static uint64_t sMask, sHead;
static int sDepth;
static const char *sOut = "/tmp/bt2_trace";

#define SEEN_N (1u << 16)
static struct { uint32_t fn, frame; uint64_t calls; } sSeen[SEEN_N];
static unsigned sSeenCount;

__attribute__((no_instrument_function))
static void note_seen(uint32_t fn) {
    uint32_t h = (fn * 2654435761u) >> 16;
    for (;;) {
        h &= SEEN_N - 1;
        if (sSeen[h].fn == fn) { sSeen[h].calls++; return; }
        if (!sSeen[h].fn) { sSeen[h].fn = fn; sSeen[h].frame = gPortVBlanks; sSeen[h].calls = 1; sSeenCount++; return; }
        h++;
    }
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *fn, void *caller) {
    unsigned f;
    uint32_t a;
    uint64_t i;
    if (!sOn) return;
    f = gPortVBlanks;
    a = (uint32_t)(uintptr_t)fn;
    if (f < sFrom) return;
    if (f > sTo) { sOn = 0; return; }
    note_seen(a);
    i = __atomic_fetch_add(&sHead, 1, __ATOMIC_RELAXED) & sMask;
    sRing[i].frame = f; sRing[i].fn = a; sRing[i].caller = (uint32_t)(uintptr_t)caller; sRing[i].depth = sDepth;
    sDepth++;
}

/* BT2_NANWATCH=1 (2026-10-28): al salir de cada funcion del juego mira x,y,z de los dos luchadores
   (**D_00387930 + i*0x1550 + 0x510, ver plat_fightlog.c); la primera funcion tras la cual alguno pasa de valido a NaN
   se informa (funcion, llamador, vblank) y se vuelca la traza. Se re-arma cuando la posicion vuelve a ser valida. */
static int sNanWatch = -1;
static uint8_t sNanPrev[2];
void bt2_trace_dump(const char *why);
#include <execinfo.h>
__attribute__((no_instrument_function))
static void nan_check(void *fn, void *caller) {
    uint32_t p, base, i;
    if (sNanWatch < 0) { const char *v = getenv("BT2_NANWATCH"); sNanWatch = v && *v && *v != '0'; }
    if (!sNanWatch) return;
    p = *(volatile uint32_t *)(uintptr_t)0x00387930u;
    if (p < 0x10000u || p >= 0x02000000u) return;
    base = *(volatile uint32_t *)(uintptr_t)p;
    if (base < 0x10000u || base + 0x2AA0u >= 0x02000000u) return;
    for (i = 0; i < 2; i++) {
        volatile float *pos = (volatile float *)(uintptr_t)(base + i * 0x1550u + 0x510u);
        float yaw = pos[0xB4 / 4];
        /* NaN en x,y,z, o yaw (pos+0xB4) fuera de [-8, 8]: el juego lo mantiene en (-pi, pi] */
        uint8_t nan = pos[0] != pos[0] || pos[1] != pos[1] || pos[2] != pos[2] || !(yaw >= -8.0f && yaw <= 8.0f);
        if (nan && !sNanPrev[i]) {
            char why[96];
            fprintf(stderr, "bt2: NANWATCH J%u: posicion NaN o yaw fuera de rango (x=%g yaw=%g) al salir de fn 0x%08X (llamada desde 0x%08X), vblank %u\n",
                    i + 1, pos[0], yaw, (uint32_t)(uintptr_t)fn, (uint32_t)(uintptr_t)caller, gPortVBlanks);
            { void *fr[2]; fr[0] = fn; fr[1] = caller; backtrace_symbols_fd(fr, 2, 2); }   /* nombres: funcion y llamador */
            snprintf(why, sizeof why, "NaN J%u tras 0x%08X vblank %u", i + 1, (uint32_t)(uintptr_t)fn, gPortVBlanks);
            sNanPrev[i] = nan;
            bt2_trace_dump(why);
        }
        sNanPrev[i] = nan;
    }
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *fn, void *caller) {
    if (sOn && sDepth > 0) sDepth--;
    nan_check(fn, caller);
}

/* Volcado crudo y rapido: <ruta>.bin = cabecera de 16 bytes {"BT2T", nEventos, vblankActual, nVistas} + eventos
   {frame, fn, caller, depth} + tabla de vistas {fn, frame, calls(u64)}. scripts/trace_sym.py lo convierte a texto con nm. */
void bt2_trace_dump(const char *why) {
    static int busy;
    char path[512];
    uint64_t n, start;
    uint32_t hdr[4];
    FILE *f;
    unsigned i;
    if (!sArmed || !sRing || busy) return;
    busy = 1; sOn = 0;
    n = sHead < sMask + 1 ? sHead : sMask + 1;
    start = sHead - n;
    snprintf(path, sizeof path, "%s.bin", sOut);
    f = fopen(path, "wb");
    if (f) {
        hdr[0] = 0x54325442u; hdr[1] = (uint32_t)n; hdr[2] = gPortVBlanks; hdr[3] = sSeenCount;
        fwrite(hdr, sizeof hdr, 1, f);
        if ((start & sMask) + n <= sMask + 1) fwrite(&sRing[start & sMask], sizeof(TraceEv), n, f);
        else {
            uint64_t first = sMask + 1 - (start & sMask);
            fwrite(&sRing[start & sMask], sizeof(TraceEv), first, f);
            fwrite(sRing, sizeof(TraceEv), n - first, f);
        }
        for (i = 0; i < SEEN_N; i++) if (sSeen[i].fn) {
            uint32_t r[4] = { sSeen[i].fn, sSeen[i].frame, (uint32_t)sSeen[i].calls, (uint32_t)(sSeen[i].calls >> 32) };
            fwrite(r, sizeof r, 1, f);
        }
        fclose(f);
    }
    fprintf(stderr, "bt2trace: %s -> %s (%llu eventos, %u funciones, vblank %u)\n", why, path, (unsigned long long)n, sSeenCount, gPortVBlanks);
    busy = 0; sOn = 1;
}

static void on_usr1(int s) { (void)s; bt2_trace_dump("SIGUSR1"); }
static void on_exit_dump(void) { bt2_trace_dump("exit"); }

__attribute__((constructor))
static void trace_init(void) {
    const char *u = getenv("BT2_ULTRALOG");
    const char *v;
    if (u && *u && *u != '0') {
        static const char *const all[] = { "BT2_SYSLOG", "BT2_FILELOG", "BT2_MC_LOG", "BT3_TEX_LOG", "BT2_DEMO_LOG", "BT3_GS_VERBOSE", "BT2_TRACE" };
        unsigned i;
        for (i = 0; i < sizeof all / sizeof *all; i++) setenv(all[i], "1", 0);
        fprintf(stderr, "bt2: ULTRALOG activo (sys/file/mc/tex/demo/gs + traza de llamadas)\n");
    }
    v = getenv("BT2_TRACE");
    if (!v || !*v || *v == '0') return;
    if ((v = getenv("BT2_TRACE_FROM"))) sFrom = (unsigned)atoi(v);
    if ((v = getenv("BT2_TRACE_TO"))) sTo = (unsigned)atoi(v);
    if ((v = getenv("BT2_TRACE_OUT"))) sOut = v;
    {
        uint64_t n = 1u << 22;
        if ((v = getenv("BT2_TRACE_RING")) && atoll(v) > 1024) { n = 1024; while (n < (uint64_t)atoll(v)) n <<= 1; }
        sRing = calloc(n, sizeof(TraceEv));
        if (!sRing) return;
        sMask = n - 1;
    }
    sArmed = 1; sOn = 1;
    signal(SIGUSR1, on_usr1);
    atexit(on_exit_dump);
    fprintf(stderr, "bt2trace: grabando (vblank %u..%u, anillo %llu eventos) -> %s\n", sFrom, sTo, (unsigned long long)(sMask + 1), sOut);
}
