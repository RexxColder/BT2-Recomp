#include "common.h"

f32 func_00210D50(void *a0, s32 a1);
s32 func_00211310(void *a0, s32 a1, s32 a2);

f32 func_0020DB08(void *arg0, s32 arg1) {
    f32 f20;
    f32 f0;

    f20 = *(f32 *)(*(u8 **)((u8 *)arg0 + 0x1530) + 0xFAC) + 0.0f;
    f0 = func_00210D50(arg0, arg1);
    f20 = f20 + f0;
    if (arg1 == 1 || arg1 == 2) {
        f20 = f20 + 30.0f;
    } else if (arg1 == 0) {
        if (func_00211310(arg0, 1, 1) != 0) {
            f20 = f20 + 40.0f;
        } else {
            f20 = f20 + 30.0f;
        }
    }
    return f20;
}
