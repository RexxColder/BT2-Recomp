#include "common.h"

s32 func_002DA360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00346DD8[] __attribute__((section(".data")));

void func_002D2540(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    u8 *t0 = (u8 *)(arg0 + 0xD30);

    if (*(s32 *)(t0 + 0x2CC) < 0) {
        *(s32 *)(t0 + 0x2CC) = 0;
        *arg3 = 1;
        return;
    }
    if (func_002DA360(arg1, arg2, *(s32 *)(t0 + 0x2CC), D_00346DD8[2]) != 0) {
        *arg3 = 1;
        return;
    }
    *arg3 = 0;
}
