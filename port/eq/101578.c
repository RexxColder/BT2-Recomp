#include "common.h"

extern u8 *D_00387F2C;

/* 0x00101578(x, which): v = int field 0x10B0 (which == 0) or 0x10AC of D_00387F2C; returns -0x3C0 when v == 0.
 * v == 9: f = x, else f = x - ((9 - v) / 10) * 128. Returns f truncated toward zero (cvt.w.s), clamped to -0x3C0..0. */
s32 func_00101578(s32 arg0, s32 arg1) {
    u8 *g = D_00387F2C;
    s32 v;
    f32 f;
    s32 r;

    if (arg1 == 0) {
        v = *(s32 *)(g + 0x10B0);
    } else {
        v = *(s32 *)(g + 0x10AC);
    }
    if (v == 0) {
        return -0x3C0;
    }
    if (v == 9) {
        f = (f32)arg0;
    } else {
        f32 d = (f32)(9 - v) / 10.0f;
        f = (f32)arg0 - d * 128.0f;
    }
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)f;
    if (r > 0) {
        r = 0;
    }
    if (r < -0x3C0) {
        r = -0x3C0;
    }
    return r;
}
