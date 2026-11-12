#include "common.h"

void func_0019D850(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;

    *(s32 *)(arg0 + 8) = arg1;
    *(s8 *)(arg0 + 3) = arg2;
    if (arg3 & 0xFF) {
        var_v0 = 0x19;
    } else {
        var_v0 = 0x64;
    }
    *(s8 *)(arg0 + 0xC) = 0;
    *(s8 *)(arg0 + 0xD) = 0;
    *(s8 *)(arg0 + 0xF) = var_v0;
    *(s8 *)(arg0 + 0xE) = var_v0;
}
