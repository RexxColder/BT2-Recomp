#include "common.h"

s32 func_002ECB18(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5);
s32 Rand_Range(s32 arg0, s32 arg1);
extern u8 D_00378D78[] __attribute__((section(".data")));

void func_002B75E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 buf[3];

    if (func_002ECB18(arg1, arg2, *(s32 *)(arg0 + 0x1A4), &buf[0], &buf[1], &buf[2]) == 0) {
        *(s32 *)(arg0 + 0x1AC) = 1;
        *(s32 *)(arg0 + 0x1B0) = buf[0];
        *(s32 *)(arg0 + 0x1B4) = buf[1];
        *(s32 *)(arg0 + 0x1B8) = buf[2];
        return;
    }
    Rand_Range((s32)D_00378D78, arg2);
}
