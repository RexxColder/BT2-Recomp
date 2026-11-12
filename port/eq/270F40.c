#include "common.h"

f32 func_00270F40(s32 *arg0, s32 *arg1) {
    u8 *base;
    s32 v1;
    s32 i;
    f32 p;
    f32 frac;

    base = (u8 *)(*arg0 + (*arg1 * 0xC0));
    p = *(f32 *)(base + 0x9C) * 128.0f;
    i = (s32)p;
    frac = p - (f32)i;
    if (frac > 0.5f || (frac == 0.5f && (i & 1))) {
        i += 1;
    } else if (frac < -0.5f || (frac == -0.5f && (i & 1))) {
        i -= 1;
    }
    v1 = i + *(s16 *)(base + 0xA6);
    if (v1 < 0) {
        v1 = 0;
    } else if (v1 >= 0x100) {
        v1 = 0xFF;
    }
    if (*(s32 *)(base + 0x48) & 8) {
        return (f32)v1 * *(f32 *)(base + 0x54) * 0.0078125f;
    }
    return (f32)v1 * 0.0078125f;
}
