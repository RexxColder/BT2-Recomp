#include "common.h"

s32 func_002B8280(void *arg0, s32 arg1, s32 arg2);
s32 Rand_Range(void *arg0, s32 arg1);
s32 func_002ECB18(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5);
s32 func_002ECD38(s32 arg0, s32 arg1, s32 arg2);
void func_002FFC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00379C50 __attribute__((section(".data")));
extern s32 D_00379C80 __attribute__((section(".data")));

void func_002BAF70(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[3];
    s32 temp_s1;

    if (func_002B8280(arg0, arg1, arg2) != 1) {
        Rand_Range((void *)&D_00379C50, arg2);
        return;
    }
    temp_s1 = *(s32 *)(arg0 + 0x48);
    if (func_002ECB18(arg1, arg2, *(s32 *)(arg0 + 0x1A4), sp, sp + 1, sp + 2) == 0) {
        func_002FFC78(temp_s1, func_002ECD38(arg1, arg1, arg2), sp[0], sp[1], sp[2]);
        return;
    }
    ((s32 (*)(void *))Rand_Range)((void *)&D_00379C80);
}
