#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1, s32 arg2, s64 arg3);
extern u8 gGfx[] __attribute__((section(".data")));

void func_00267C58(s64 arg0, s32 arg1) {
    s32 buf[48];
    s64 t1;
    s32 t2;
    s32 v0c;
    s32 i;
    s64 a3v;

    t1 = arg0 << 32;
    t2 = arg1 & 0xFF;
    if (!(*(s32 *)(gGfx + 0x234) & 1)) {
        v0c = 0x80070;
    } else {
        v0c = 0x80000;
    }
    /* words at +0x60..+0xBF are the packet; +0x00..+0x5F is its copy (the DMA source) */
    buf[24] = 0x10000005;
    buf[25] = 0;
    buf[26] = 0x10000000;
    buf[27] = 0x50000005;
    buf[28] = 0x8004;
    buf[29] = 0x10000000;
    buf[30] = 0xE;
    buf[31] = 0;
    buf[32] = v0c;
    buf[33] = (s32)(t1 >> 32);
    buf[34] = 0x4C;
    buf[35] = 0;
    buf[36] = 0x64;
    buf[37] = (t2 == 0) ? 0x80 : 0x40;
    buf[38] = 0x42;
    buf[39] = 0;
    buf[40] = (s32)(((t2 & 0xFF) << 14) | 0x50000);
    buf[41] = 0;
    buf[42] = 0x47;
    buf[43] = 0;
    buf[44] = t2;
    buf[45] = 0;
    buf[46] = 0x4A;
    buf[47] = 0;
    a3v = *(s64 *)&buf[44];
    for (i = 0; i < 24; i++) {
        buf[i] = buf[24 + i];
    }
    Dma_AddData((s32)buf, 0x60, (s32)(buf + 48), a3v);
}
