#include "common.h"

void func_00331710(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00355374 __attribute__((section(".data")));
extern u32 D_00355388 __attribute__((section(".data")));
extern u8 D_0037DF68[] __attribute__((section(".data")));

void func_002FC1D8(void) {
    D_00355388 = 0;
loop_1:
    if (D_00355374 == 1) {
        D_00355388 += 1;
        if (D_00355388 <= 0x19640000U) {
            goto loop_1;
        }
        func_00331710((s32)D_0037DF68, (s32)&D_00355388, 0x19640000, 1);
    }
}
