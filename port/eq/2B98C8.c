#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_00379510[] __attribute__((section(".data")));

s32 func_002B98C8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 temp_v1;

    temp_v1 = *(u32 *)(arg0 + 0x8C);
    if (temp_v1 == 2) {
        return 2;
    }
    if (temp_v1 == 3) {
        return 3;
    }
    if (temp_v1 == 1) {
        return 1;
    }
    Rand_Range((s32)D_00379510, arg1, arg2, arg3);
    return 1;
}
