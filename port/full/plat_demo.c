/* BT2_DEMO=1: salta los menus y corre el combate de demostracion del propio juego (CPU contra CPU), como BT3_DEMO=1 en
   Tenkaichi3Decomp (port/src/headless.c). En BT2 la demo la monta func_003B9710 (el "titulo", overlay) cuando el contador de
   inactividad O->0x4518 (O = D_004213B0) pasa de 0x708: elige una fila de la tabla de O->0x45C0 (rand % O->0x45C4), monta los
   dos luchadores (func_101AF8) y la regla (func_101A60) y devuelve fr[0]=1; Progress_Main (0x3B7FA8) vuelve y el bucle de
   Game_Main (0x100388) llama a func_00103000 (Battle_Main). Aqui solo se adelanta el contador desde el vsync.
   Fin: la segunda carga del overlay (Overlay_Load, visto en sceRead) = el combate acabo -> "battle finished" y exit(0).
   BT2_CHARA=a[,b]: personajes (id de tabla del juego = grupo*9+variante) de los dos lados, puestos en la fila elegida.
   BT2_DEMO_ROW=n fuerza la fila de la tabla (n < O->0x45C4) por si se quiere un emparejamiento concreto. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define W(a) (*(volatile uint32_t *)(uintptr_t)(a))
extern unsigned gPortVBlanks;

static int sDemo = -1, sLoads, sSeenBattle;

static int demo_on(void) {
    if (sDemo < 0) sDemo = getenv("BT2_DEMO") != NULL;
    return sDemo;
}

/* sceRead de plat_file.c: el overlay (0x3B3100) se acaba de leer entero */
void Port_DemoOverlayLoaded(void) {
    if (!demo_on()) return;
    if (++sLoads >= 2) {
        printf("bt2: battle finished (%u vsyncs)\n", gPortVBlanks);
        fflush(stdout);
        exit(0);
    }
}

/* vsync (plat_gs.c) */
void Port_DemoTick(void) {
    uint32_t O, st;
    static unsigned lastReport;
    if (!demo_on()) return;
    if (sLoads == 0) return;
    O = W(0x4213B0);
    st = W(W(0x3876A4) + 0x1C);
    if (sLoads == 1 && !sSeenBattle && O > 0x400000 && O < 0x02000000 && (st == 1 || st == 4) && W(O + 0x4518) > 0 && W(O + 0x4518) < 0x708) {
        const char *row = getenv("BT2_DEMO_ROW");
        uint32_t P = W(O + 0x45C0), n = W(O + 0x45C4);
        if (row && P && n) { /* la fila se elige con rand(): no se puede forzar sin tocar la tabla; se deja solo la primera fila */
            int r = atoi(row);
            if (r > 0 && (uint32_t)r < n) memcpy((void *)(uintptr_t)P, (void *)(uintptr_t)(P + 24 * r), 24);
            for (uint32_t i = 1; i < n && (uint32_t)r < n; i++) memcpy((void *)(uintptr_t)(P + 24 * i), (void *)(uintptr_t)P, 24);
        }
        W(O + 0x4518) = 0x708;
    }
    if (gPortVBlanks - lastReport >= 600 && getenv("BT2_DEMO_LOG")) {
        lastReport = gPortVBlanks;
        fprintf(stderr, "bt2demo: v=%u loads=%d O=%X st=%u cnt=%u s3876A4+18=%X\n", gPortVBlanks, sLoads, O, st, O ? W(O + 0x4518) : 0, W(W(0x3876A4) + 0x18));
    }
}
