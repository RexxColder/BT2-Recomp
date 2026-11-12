#include "common.h"

/* D_0036C5F8 esta en 0x36C5F8 (alineado a 8, no a 16): con __builtin_memcpy el compilador usa movaps y el host cae con
   SIGSEGV (general protection). Copia por palabras volatiles. */
extern u32 D_0036C5F8[0x30 / 4];
extern void Dma_AddData();

void func_0010C6E8(void) {
    u8 pkt[0x30] __attribute__((aligned(16)));
    volatile u32 *src = (volatile u32 *)D_0036C5F8;
    u32 *dst = (u32 *)pkt;
    s32 i;

    for (i = 0; i < 0x30 / 4; i++) {
        dst[i] = src[i];
    }
    Dma_AddData(pkt, 0x30);
}
