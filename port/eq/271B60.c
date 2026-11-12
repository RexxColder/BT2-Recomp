#include "common.h"

extern s32 D_003B0A84;

s32 Dma_BeginDirect(s32 arg0, s32 arg1);
s32 Dma_EndDirect(s32 arg0);

/* Writes a DMA/GIF packet list for one textured strip into the direct buffer: a header (tag + register
 * sets), one quadword per 32-pixel column step (x offset, scaled width), the closing registers, and a
 * final tag selected by D_003B0A84. Returns the end of the written list. */
s32 func_00271B60(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    s32 v7 = (a2 < 0) ? a2 + 31 : a2;
    s32 v12 = v7 >> 5;
    s32 v16 = (a2 < 0) ? a2 + 63 : a2;
    s64 *p;
    s64 *tag;
    s32 v20;
    s32 cnt;
    s64 v22;

    p = (s64 *)Dma_BeginDirect(a1, a2);

    p[0] = 0x1000000000000009LL;
    p[1] = 14;
    p += 2;
    p[0] = (s64)a1 | ((s64)(v16 >> 6) << 16) | ((s64)a4 << 32);
    p[1] = 76;
    p += 2;
    p[0] = 0x1310000E0LL;
    p[1] = 78;
    p += 2;
    p[0] = 0;
    p[1] = 24;
    p += 2;
    p[0] = ((s64)a2 << 16) | ((s64)a3 << 48);
    p[1] = 64;
    p += 2;
    p[0] = 196608;
    p[1] = 71;
    p += 2;
    p[0] = a5;
    p[1] = 66;
    p += 2;
    p[0] = 0;
    p[1] = 74;
    p += 2;
    p[0] = 70;
    p[1] = 0;
    p += 2;
    p[0] = a6;
    p[1] = 1;
    p += 2;

    tag = p;
    p += 2;

    v20 = 0;
    for (cnt = v12; cnt > 0; cnt--) {
        p[0] = (s64)(16 * v20);
        p[1] = (s64)(16 * (v20 + 32)) | ((s64)(16 * a3) << 16);
        p += 2;
        v20 += 32;
    }

    tag[0] = (s64)v12 | 0x2400000000008000LL;
    tag[1] = 85;

    p[0] = 0x1000000000008006LL;
    p[1] = 14;
    p += 2;

    p[1] = 76;
    v22 = 0x80070;
    if ((D_003B0A84 & 1) != 0) {
        v22 = 0x80000;
    }
    p[0] = v22;
    p += 2;

    p[0] = 0x720000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x1BF000001FF0000LL;
    p[1] = 64;
    p += 2;
    p[0] = 458752;
    p[1] = 71;
    p += 2;
    p[0] = 0x1310000E0LL;
    p[1] = 78;
    p += 2;
    p[0] = 0;
    p[1] = 8;
    p += 2;

    return Dma_EndDirect((s32)p);
}
