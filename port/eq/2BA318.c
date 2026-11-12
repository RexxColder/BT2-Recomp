#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1);
extern u8 D_003798B8[] __attribute__((section(".data")));

void func_002BA318(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg2 <= 0x1FFFF) {
        Rand_Range((s32)D_003798B8, arg1);
    }
    *(s32 *)(arg0 + 0x188 + 4) = arg2;
    *(s32 *)(arg0 + 0x188) = arg1;
}
