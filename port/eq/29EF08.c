#include "common.h"

s32 Dma_Alloc(s32 arg0);

/* 0x0029EF08(chain): p = Dma_Alloc(0x20) (eight words): 0x50000001 (DMA call | 1), chain & 0x0FFFFFFF, 0x10000000,
 * 0, 0x15000000, 0x3000092, 0x20001B2, 0. Returns p. */
s32 func_0029EF08(s32 arg0) {
    u32 *p = (u32 *)Dma_Alloc(0x20);

    p[0] = 0x50000001;
    p[1] = (u32)arg0 & 0x0FFFFFFF;
    p[2] = 0x10000000;
    p[3] = 0;
    p[4] = 0x15000000;
    p[5] = 0x3000092;
    p[6] = 0x20001B2;
    p[7] = 0;
    return (s32)p;
}
