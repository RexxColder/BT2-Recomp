#include "common.h"

u32 func_002D8278(s32 arg0, s32 arg1);
s32 strncmp(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037AE20[] __attribute__((section(".data")));

s32 func_002D8430(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (arg0 == 0 || arg1 < 0) {
        return 0;
    }
    var_v0 = 0;
    if (func_002D8278(arg0, arg1) >= 2U) {
        var_v0 = strncmp(arg0 + 0x16, (s32)D_0037AE20, 1) != 0;
    }
    return var_v0;
}
