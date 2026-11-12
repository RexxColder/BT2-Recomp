#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_001F9FB0(u8 *arg0, s32 arg1) {
    u8 *s0;
    f32 f0;
    f32 f2;
    s32 r;

    r = 0;
    s0 = *(u8 **)(arg0 + 0x1530) + 0xBD0;
    f0 = *(f32 *)(s0 + 0x1C) - *(f32 *)(s0 + 0x20);
    *(f32 *)(s0 + 0x1C) = f0;
    if (f0 < 0.0f) {
        *(f32 *)(s0 + 0x1C) = 0.0f;
        func_002113C0((s32)arg0, 2, 0x200, 0);
    } else {
        func_002113C0((s32)arg0, 2, 0x200, 1);
    }
    f2 = *(f32 *)(s0 + 0x10);
    *(f32 *)(s0 + 0x14) = f2;
    if (!(arg1 & 1) || *(f32 *)(s0 + 0x1C) == 0.0f) {
        f0 = f2 + *(f32 *)(s0 + 0x18);
        *(f32 *)(s0 + 0x10) = f0;
        if (*(f32 *)(s0 + 8) <= f0) {
            func_002113C0((s32)arg0, 2, 1, 1);
            r = 1;
            *(f32 *)(s0 + 0x10) = *(f32 *)(s0 + 8);
        }
    }
    return r;
}
