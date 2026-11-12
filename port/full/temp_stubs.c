/* Funciones DEL JUEGO sin C todavia (batch 10), escritas a mano desde el asm para poder seguir. Son debiles: en cuanto
   exista el C en src/ o port/eq/ el enlace usa ese y esto desaparece. Lista y motivo en TEMP_STUBS.txt. */
#include <stdint.h>
#include <string.h>
#define TEMP __attribute__((weak))
#define W(a) (*(volatile uint32_t *)(uintptr_t)(a))
#define B(a) (*(volatile uint8_t *)(uintptr_t)(a))
extern uint32_t func_0028BAA8(int32_t size);   /* port/eq/28BAA8.c */

/* 0x00100258: sceGsResetGraph + sceGsSetDefDBuff + FlushCache + sceGsSyncV + 2 x (sceGsPutDrawEnv + sceGsSyncPath) */
TEMP void func_00100258(void) {}

/* 0x0028AFA0: D_00387EB0=D_00387EB1=0; cuatro buffers (1 MB, 1 MB, 1 KB, 1 KB) en D_0038A628[]; gDmaCur = buffer 0 */
TEMP void func_0028AFA0(void) {
    B(0x387EB0) = 0; B(0x387EB1) = 0;
    W(0x38A628) = func_0028BAA8(0x100000);
    W(0x38A62C) = func_0028BAA8(0x100000);
    W(0x38A630) = func_0028BAA8(0x400);
    W(0x38A634) = func_0028BAA8(0x400);
    W(0x387EAC) = W(0x38A628 + 4 * B(0x387EB0));
}

/* 0x0028BC08: memset(D_0038A638, 0, 0x60); D_00387EB4 = 0; D_0038A638[idx*2] = 0x5010; D_0038A638[idx*2+1] = 0x1BAFEF */
TEMP void func_0028BC08(void) {
    memset((void *)(uintptr_t)0x38A638, 0, 0x60);
    W(0x387EB4) = 0;
    W(0x38A638 + W(0x387EB4) * 8) = 0x5010;
    W(0x38A638 + W(0x387EB4) * 8 + 4) = 0x1BAFEF;
}

/* 0x00102360: reinicia los bloques de la estructura apuntada por D_003876A4 */
TEMP void func_00102360(void) {
    uint32_t p = W(0x3876A4);
    int i;
    if (!p) return;
    W(p + 0x28) = 0;
    memset((void *)(uintptr_t)(p + 0x2C), 0, 0x14);
    memset((void *)(uintptr_t)(p + 0x40), 0, 0x48);
    memset((void *)(uintptr_t)(p + 0x88), 0, 0x308);
    memset((void *)(uintptr_t)(p + 0x390), 0, 0xE8);
    memset((void *)(uintptr_t)(p + 0x478), 0, 0x14);
    memset((void *)(uintptr_t)(p + 0x48C), 0, 0x28);
    memset((void *)(uintptr_t)(p + 0x4B4), 0, 0xC);
    W(p + 0x4C0) = 0; W(p + 0x4C4) = 0;
    for (i = 0; i < 5; i++) { W(p + 0x390 + 4 * i) = 0; W(p + 0x3A4 + 4 * i) = 1; }
}

/* 0x003B7FA8: Progress_Main, la entrada del overlay DBZP.BIN (menus: logos, titulo, ...). El overlay (507 funciones en
   0x3B3100..0x421300) aun no tiene C: sin esto el bucle principal del juego caeria en Battle_Main sin batalla montada.
   Se informa donde esta el programa y se termina. Cuando exista el C del overlay este stub desaparece solo. */
#include <stdio.h>
#include <stdlib.h>
extern unsigned gPortVBlanks;
#ifndef BT2_FALLBACK   /* con el relleno (recomp_shim.cpp) Progress_Main corre recompilado */
TEMP long func_3B7FA8(long arg) {
    (void)arg;
    fprintf(stderr, "bt2full: llegado al overlay (Progress_Main 0x3B7FA8) tras %u vsyncs: el overlay DBZP.BIN no tiene C todavia. Fin.\n", gPortVBlanks);
    exit(0);
}
#endif
