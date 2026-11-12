#include "common.h"

extern u8 *D_003879A0;

void func_0024CD30(s32 arg0) {
    s32 var_t4 = 0;

    do {
        u8 *P = D_003879A0;
        s32 t0 = var_t4 * 4;
        s32 t3 = t0 + 0x14C;
        s32 a3 = *(s32 *)(P + 0x10);
        s32 t2 = *(s32 *)(P + t3);
        s32 a1 = *(s32 *)(P + 0x1CC);
        s32 t1 = *(s32 *)(P + arg0 * 4 + 0x1E8);
        s32 v1 = a1 * 7 + var_t4;
        s32 x;
        s32 y;
        s32 z;
        s32 w;

        var_t4 += 1;
        x = *(s32 *)((u8 *)(v1 * 44 + t1));
        y = (x << 2) + a3;
        z = *(s32 *)((u8 *)y + 4);
        *(s32 *)(P + t0 + 0x174) = t2;
        w = a3 + (((u32)z >> 2) * 4);
        *(s32 *)(P + t3) = *(s32 *)((u8 *)w + 0x10);
    } while (var_t4 < 7);
}
