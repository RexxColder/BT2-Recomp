#include "common.h"

void func_00312680(u8 *arg0, u8 *arg1, f32 farg0);
void func_001E0EA0(u8 *arg0);
s32 func_001E1E28(u8 *arg0, u8 *arg1);

s32 func_001E0C80(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5,
                  f32 farg0, f32 farg1) {
    u8 cp[0x1B0];
    s32 k;
    f32 fs;
    f32 v31;
    f32 w;
    f32 z;

    __builtin_memcpy(cp, arg1, 0x1B0);
    __builtin_memcpy(arg0, cp, 0x1B0);

    fs = farg0;
    if (fs == 0.0f) {
        fs = 1.0f;
    }

    if (*(s32 *)arg0 < 4) {
        *(s32 *)(arg0 + 0x164) = 0;
        *(s32 *)(arg0 + 0x1A8) = 0;
    }

    *(f32 *)(arg0 + 0x150) = arg2[0];
    *(f32 *)(arg0 + 0x154) = arg2[1];
    *(f32 *)(arg0 + 0x158) = arg2[2];
    *(f32 *)(arg0 + 0x15C) = arg2[3];
    func_00312680(arg0 + 0x120, arg0 + 0x120, fs);

    func_00312680(arg0 + 0x130, arg0 + 0x130, fs);
    func_00312680(arg0 + 0x140, arg0 + 0x140, fs);
    func_00312680(arg0 + 0x110, arg0 + 0x110, fs);

    *(f32 *)(arg0 + 0x88) = *(f32 *)(arg0 + 0x88) + farg1;
    func_001E0EA0(arg0);

    for (k = 0; k < 4; k++) {
        v31 = arg3[k];
        if (v31 != 0.0f) {
            *(f32 *)(arg0 + 0xB0 + 4 * k) = v31;
            *(f32 *)(arg0 + 0xC0 + 4 * k) = arg3[k];
        }
        w = arg4[k];
        if (w != 0.0f) {
            *(f32 *)(arg0 + 0xD0 + 4 * k) = w;
        }
        z = arg5[k];
        if (z != 0.0f) {
            *(f32 *)(arg0 + 0xE0 + 4 * k) = z;
        }
    }
    *(s32 *)(arg0 + 0x194) = 0;
    *(s32 *)(arg0 + 0x198) = 0;

    return func_001E1E28(arg0 + 0x10, arg0 + 0x60);
}
