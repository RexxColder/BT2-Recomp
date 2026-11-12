#include "common.h"

f32 EftMath_WrapAngle(f32 arg0);
f32 cosf(f32 x);
f32 sinf(f32 x);

void func_001E99B8(u8 *arg0, s32 arg1) {
    u8 *t0 = *(u8 **)arg0;
    u8 *v = arg0 + 4 * (arg1 & 0xFF);
    s32 a3;
    f32 e0;
    f32 a;

    a3 = *(s32 *)(t0 + 0x98);
    if ((a3 & 0x10000) == 0) {
        *(f32 *)(arg0 + 0xE4) = *(f32 *)(arg0 + 0xE4) + *(f32 *)(v + 0xE8);
    }
    a3 = *(s32 *)(t0 + 0x98);
    if ((a3 & 0x2000) == 0) {
        *(f32 *)(arg0 + 0xF0) = *(f32 *)(arg0 + 0xF0) + *(f32 *)(v + 0xF4);
        a3 = *(s32 *)(t0 + 0x98);
    }
    if ((a3 & 0x400) == 0) {
        *(f32 *)(arg0 + 0xFC) = *(f32 *)(arg0 + 0xFC) + *(f32 *)(v + 0x100);
        a3 = *(s32 *)(t0 + 0x98);
    }
    if ((a3 & 0x80) == 0) {
        *(f32 *)(arg0 + 0xC8) = *(f32 *)(arg0 + 0xC8) + *(f32 *)(v + 0xCC);
    }

    e0 = *(f32 *)(arg0 + 0xE0) + *(f32 *)(arg0 + 0xDC) * *(f32 *)(arg0 + 0xE4);
    *(f32 *)(arg0 + 0xE0) = e0;

    a = EftMath_WrapAngle(e0);
    *(f32 *)(arg0 + 0x70) = cosf(a) * *(f32 *)(arg0 + 0xF0);

    a = EftMath_WrapAngle(*(f32 *)(arg0 + 0xE0));
    *(f32 *)(arg0 + 0x7C) = 1.0f;
    *(f32 *)(arg0 + 0x74) = sinf(a) * *(f32 *)(arg0 + 0xF0);
    *(f32 *)(arg0 + 0x78) = *(f32 *)(arg0 + 0x78) + *(f32 *)(arg0 + 0xC8);
}
