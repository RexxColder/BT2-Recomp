#include "common.h"

extern u8 *D_00387F2C;

/* 0x002494C0: v = *(D_00387F2C + 0x10B0). 0 -> -0x3C0; 9 -> -80; otherwise truncates toward zero-even of
 * (float)(v - 9) * 24.0f + farg0 (cvt.w.s). */
s32 func_002494C0(f32 farg0) {
    s32 v1 = *(s32 *)(D_00387F2C + 0x10B0);
    f32 x;
    s32 t;

    if (v1 == 0) {
        return -0x3C0;
    }
    if (v1 == 9) {
        return -80;
    }
    x = (f32)(v1 - 9) * 24.0f + farg0;
    t = (s32)x;
    return t;
}
