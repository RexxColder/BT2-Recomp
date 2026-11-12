#include "common.h"

extern u8 *D_00387F2C;

/* 0x00297F58(x, which): v = int field 0x10B0 (which == 0) or 0x10AC of D_00387F2C; 0 when v == 0. v == 9: f = x,
 * else f = x - x * ((9 - v) / 10). Returns f truncates toward zero and clamped to 0..127. */
s32 func_00297F58(s32 arg0, s32 arg1) {
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
        return 0;
    }
    if (v == 9) {
        f = (f32)arg0;
    } else {
        f32 x = (f32)arg0;
        f32 d = (f32)(9 - v) / 10.0f;
        f = x - x * d;
    }
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)f;
    if (r >= 0x80) {
        r = 0x7F;
    }
    if (r < 0) {
        r = 0;
    }
    return r;
}
