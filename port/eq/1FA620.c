#include "common.h"

f32 func_001FA588(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_003857B4;
extern f32 D_003857B8;
extern f32 D_003857BC;
extern f32 D_003857C0;
extern u8 *D_003876A0;

f32 func_001FA620(s32 arg0, s32 arg1, s32 arg2) {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 t;
    u8 *s0;

    f0 = 1.0f;
    s0 = (u8 *)arg0 + 0x150;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) == 0) {
        f2 = func_001FA588(arg0, arg1, arg2);
        f1 = *(f32 *)(s0 + 0xA0);
        if (f1 < f2) {
            t = f1 + D_003857B4;
            *(f32 *)(s0 + 0xA0) = t;
            if (f2 < t) {
                *(f32 *)(s0 + 0xA0) = f2;
                f1 = f2;
            } else {
                f1 = t;
            }
        }
        if (f2 < f1) {
            t = f1 - D_003857B8;
            *(f32 *)(s0 + 0xA0) = t;
            if (t < f2) {
                *(f32 *)(s0 + 0xA0) = f2;
            }
        }
        if (func_00211310(arg0, 0xE, 0x400) != 0) {
            *(f32 *)(s0 + 0xA0) = D_003857BC;
        }
        if (func_00211310(arg0, 0xE, 0x200) != 0) {
            *(f32 *)(s0 + 0xA0) = 0.25f;
        }
        if (func_00211310(arg0, 0xE, 0x400) != 0) {
            *(f32 *)(s0 + 0xA0) = D_003857C0;
        }
        f0 = *(f32 *)(s0 + 0xA0);
    }
    return f0;
}
