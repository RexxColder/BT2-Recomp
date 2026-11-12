#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);

void func_001B0298(s32 arg0, s32 arg1, f32 farg0) {
    u8 *m;
    f32 s;
    f32 c;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 xs;
    f32 ys;
    f32 zs;

    m = (u8 *)arg0;
    s = sinf(-farg0);
    c = cosf(-farg0);
    x = *(f32 *)(arg1 + 8);
    y = *(f32 *)(arg1 + 0);
    z = *(f32 *)(arg1 + 4);
    t = 1.0f - c;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    *(s32 *)(m + 0x0C) = 0;
    *(f32 *)(m + 0x3C) = 1.0f;
    *(s32 *)(m + 0x1C) = 0;
    *(s32 *)(m + 0x2C) = 0;
    *(s32 *)(m + 0x30) = 0;
    *(s32 *)(m + 0x34) = 0;
    *(s32 *)(m + 0x38) = 0;
    *(f32 *)(m + 0x10) = (y * z * t) - xs;
    *(f32 *)(m + 0x24) = (z * x * t) - ys;
    *(f32 *)(m + 0x20) = (y * x * t) + zs;
    *(f32 *)(m + 0x28) = c + (x * x * t);
    *(f32 *)(m + 0x00) = c + (y * y * t);
    *(f32 *)(m + 0x14) = c + (z * z * t);
    *(f32 *)(m + 0x04) = (y * z * t) + xs;
    *(f32 *)(m + 0x08) = (y * x * t) - zs;
    *(f32 *)(m + 0x18) = (z * x * t) + ys;
}
