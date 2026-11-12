#include "common.h"

extern u8 *D_003876A0;

void func_00263DA8(f32 farg0, f32 farg1, u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 frac;
    f32 t;
    s32 i;

    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 46)) {
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) | 8;
        *(f32 *)(arg0 + 0x38) = 128.0f;
        return;
    }
    temp_f0 = *(f32 *)(arg0 + 0x3C);
    if (farg1 < temp_f0) {
        *(s32 *)(arg0 + 0x38) = 0;
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) & ~8;
        return;
    }
    if (!(farg0 < temp_f0)) {
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) | 8;
        *(f32 *)(arg0 + 0x38) = 128.0f;
        return;
    }
    temp_f0_2 = ((temp_f0 - farg0) / (farg1 - farg0)) * 128.0f;
    t = 128.0f - temp_f0_2;
    *(f32 *)(arg0 + 0x38) = t;
    i = (s32)t;
    frac = t - (f32)i;
    if (frac > 0.5f || (frac == 0.5f && (i & 1))) {
        i += 1;
    } else if (frac < -0.5f || (frac == -0.5f && (i & 1))) {
        i -= 1;
    }
    if (i != 0) {
        *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) | 8;
        return;
    }
    *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) & ~8;
}
