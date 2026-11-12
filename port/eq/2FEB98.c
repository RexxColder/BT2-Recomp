#include "common.h"

extern u8 D_00356D00[] __attribute__((section(".data")));
extern s32 D_00356D04 __attribute__((section(".data")));

void func_002FEB98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00356D04 = arg3;
    D_00356D00[2] = (u8)arg2;
    D_00356D00[0] = (u8)arg0;
    D_00356D00[1] = (u8)arg1;
}
