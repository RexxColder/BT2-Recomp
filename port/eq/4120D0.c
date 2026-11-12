#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));

/* 0x004120D0: for k in 0..6, with rec = G + 80*arg0 + 4*k (G = *D_0042BB7C): word at rec+0x1B8 gets the old word
 * at rec+0x190, then word at rec+0x190 gets a value fetched through three index tables (w, x, y) and a3 = *(G+0x28). */
void func_004120D0(s32 arg0) {
    s32 k;

    for (k = 0; k < 7; k++) {
        u8 *g = D_0042BB7C;
        s32 off = arg0 * 0x50 + k * 4;
        s32 w = *(s32 *)(g + 0xC + 0x290 + arg0 * 4);
        u8 *t2 = *(u8 **)(g + arg0 * 4 + 0x2D8);
        u8 *a3 = *(u8 **)(g + 0x28);
        s32 x = *(s32 *)(g + 0xC + 0x240 + (2 * arg0 + w) * 4);
        s32 v = x * 7 + k;
        s32 y = *(s32 *)(t2 + v * 44);
        s32 z = *(s32 *)(a3 + y * 4 + 4);
        s32 t1 = *(s32 *)(g + off + 0x190);
        s32 a0;

        z = (s32)((u32)z & ~3u);
        *(s32 *)(g + off + 0x1B8) = t1;
        a3 = a3 + z;
        a0 = *(s32 *)(a3 + 0x10);
        *(s32 *)(g + off + 0x190) = a0;
    }
}
