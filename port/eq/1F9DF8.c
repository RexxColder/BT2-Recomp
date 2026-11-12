#include "m2c_macros.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 BtlAnim_SetBlend(void *arg0, f32 farg0) {
    s32 result;

    result = func_002113C0((s32)arg0, 2, 8, 1);
    *(f32 *)((u8 *)arg0 + 0x8F0) = farg0;
    return result;
}
