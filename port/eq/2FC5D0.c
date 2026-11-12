#include "common.h"

s32 func_00331710(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_0035537C __attribute__((section(".data")));
extern s32 D_003553AC __attribute__((section(".data")));
extern u8 D_0037E088[] __attribute__((section(".data")));

s32 func_002FC5D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    D_0035537C = (s8)arg0;
    temp_v0 = D_0035537C;
    D_003553AC = temp_v0;
    if (arg0 == 1) {
        return func_00331710((s32)D_0037E088, 1, (s32)&D_003553AC, arg3);
    }
    return temp_v0;
}
