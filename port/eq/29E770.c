#include "common.h"

/* 0x0029E770: p = Dma_Alloc(0x20); p[0] = 0x50000001; p[1] = a0 & 0x0FFFFFFF; p[2] = 0x10000000; p[3] = 0;
   p[4] = 0x15000000; p[5] = 0x0300008D; p[6] = 0x020001B4; p[7] = 0; returns p (v0). */
s32 Dma_Alloc(s32 arg0);

u8 *func_0029E770(s32 a0) {
    u8 *p;

    p = (u8 *)Dma_Alloc(0x20);
    *(s32 *)(p + 0x4) = a0 & 0x0FFFFFFF;
    *(s32 *)(p + 0x0) = 0x50000001;
    *(s32 *)(p + 0x8) = 0x10000000;
    *(s32 *)(p + 0x10) = 0x15000000;
    *(s32 *)(p + 0x14) = 0x0300008D;
    *(s32 *)(p + 0x18) = 0x020001B4;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0xC) = 0;
    return p;
}
