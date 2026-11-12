#include "common.h"

f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 sinf(f32 farg0);
extern f32 D_003857C4;
extern f32 D_003857C8;
extern f32 D_003857CC;
extern f32 D_003857D0;
extern f32 D_003857D4;
extern f32 D_003857D8;
extern f32 D_003857DC;
extern u8 *D_003876A0;

f32 func_001FA730(u8 *arg0) {
    u8 *s0;
    f32 f12;
    f32 t;
    f32 result;

    result = 0.0f;
    s0 = arg0 + 0x150;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) == 0 && *(u8 *)(arg0 + 0x208) != 0) {
        f12 = *(f32 *)(s0 + 0x1C);
        if (func_00211310((s32)arg0, 0, 2) != 0) {
            t = BtlUtil_WrapAngle(f12 + D_003857C4);
            *(f32 *)(s0 + 0x1C) = t;
            f12 = t;
        } else {
            if (D_003857C8 < f12) {
                t = D_003857CC - f12;
                *(f32 *)(s0 + 0x1C) = t;
                f12 = t;
            }
            if (f12 < D_003857D0) {
                t = D_003857D4 - f12;
                *(f32 *)(s0 + 0x1C) = t;
                f12 = t;
            }
            if (f12 > 0.0f) {
                t = f12 - D_003857D8;
                *(f32 *)(s0 + 0x1C) = t;
                if (t < 0.0f) {
                    *(f32 *)(s0 + 0x1C) = 0.0f;
                    f12 = 0.0f;
                } else {
                    f12 = t;
                }
            }
            if (f12 < 0.0f) {
                t = f12 + D_003857DC;
                *(f32 *)(s0 + 0x1C) = t;
                if (t > 0.0f) {
                    *(f32 *)(s0 + 0x1C) = 0.0f;
                    f12 = 0.0f;
                } else {
                    f12 = t;
                }
            }
        }
        result = sinf(f12) * 1.5f;
    }
    return result;
}
