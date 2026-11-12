#include "common.h"

extern u8 *D_00387F2C;

/* 0x001013B0: v = *(D_00387F2C + 0x10A8). 0 -> -0x3C0; 9 -> -80; otherwise truncates toward zero-even of
 * (float)(v - 9) * 24.0f + -80.0f (cvt.w.s). */
s32 func_001013B0(void) {
    s32 v1 = *(s32 *)(D_00387F2C + 0x10A8);
    f32 x;
    s32 t;

    if (v1 == 0) {
        return -0x3C0;
    }
    if (v1 == 9) {
        return -80;
    }
    x = (f32)(v1 - 9) * 24.0f + (-80.0f);
    t = (s32)x;
    return t;
}
