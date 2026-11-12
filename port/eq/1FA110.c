#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001FA110(u8 *arg0, s32 arg1) {
    u8 *s0;
    f32 f0;
    f32 t;

    s0 = *(u8 **)(arg0 + 0x1530) + 0xBD0;
    f0 = *(f32 *)(s0 + 0x1C) - *(f32 *)(s0 + 0x20);
    *(f32 *)(s0 + 0x1C) = f0;
    if (f0 < 0.0f) {
        *(f32 *)(s0 + 0x1C) = 0.0f;
        func_002113C0((s32)arg0, 2, 0x200, 0);
    } else {
        func_002113C0((s32)arg0, 2, 0x200, 1);
    }
    t = *(f32 *)(s0 + 0x10);
    *(f32 *)(s0 + 0x14) = t;
    if (!(arg1 & 1) || *(f32 *)(s0 + 0x1C) == 0.0f) {
        t = t + 2.0f;
        *(f32 *)(s0 + 0x10) = t;
        if (*(f32 *)(s0 + 8) <= t) {
            *(f32 *)(s0 + 0x10) = 0.0f;
        }
    }
}
