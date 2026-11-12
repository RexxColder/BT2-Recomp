#include "common.h"

void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

s32 func_0025B778(s32 arg0, s32 arg1) {
    f32 v[4];
    f32 inv;
    f32 x;
    f32 y;
    f32 z;

    sceVu0ApplyMatrix((s32)v, arg0 + 0x100, arg1);
    inv = 1.0f / v[3];
    x = (v[0] * inv) - 1792.0f;
    y = (v[1] * inv) - 1824.0f;
    z = v[2] * inv;

    if (z < 0.0f) {
        return 0;
    }
    if (x < (f32)*(s32 *)(arg0 + 0x200)) {
        return 0;
    }
    if ((f32)*(s32 *)(arg0 + 0x204) < x) {
        return 0;
    }
    if (y < (f32)*(s32 *)(arg0 + 0x208)) {
        return 0;
    }
    if ((f32)*(s32 *)(arg0 + 0x20C) < y) {
        return 0;
    }
    return 1;
}
