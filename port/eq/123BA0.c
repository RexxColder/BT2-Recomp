#include "common.h"

f32 func_00123BA0(u8 *arg0, s32 arg1, s32 arg2) {
    f32 v = 0.0f;

    if (arg1 != 0xFF && arg2 >= 0) {
        s32 idx = arg1 * *(s32 *)(arg0 + 0xC) + arg2;
        v = *(f32 *)(*(u8 **)(arg0 + 0x68) + idx * 4);
    }
    return v;
}
