#include "common.h"

void Rand_Range(s32 arg0);
void func_002B3C80(s32 arg0);
void func_002B6700(s32 arg0);
s32 func_002C30A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002CE680(s32 arg0);
extern u8 D_00377FE8[] __attribute__((section(".data")));
extern u8 D_00378020[] __attribute__((section(".data")));
extern u8 func_002B6818[] __attribute__((section(".data")));

s32 func_002B3F78(u8 *arg0) {
    s32 temp_s1;

    temp_s1 = *(s32 *)(arg0 + 0x3C);
    *(s32 *)(arg0 + 0x3C) = 0;
    if (func_002CE680(temp_s1) != 0) {
        Rand_Range((s32)D_00377FE8);
        return -1;
    }
    *(s32 *)(arg0 + 0x3C) = temp_s1;
    if (func_002C30A0(temp_s1, (s32)func_002B6818, (s32)arg0) != 0) {
        func_002B6700(-0x12F);
        Rand_Range((s32)D_00378020);
        return -1;
    }
    func_002B3C80((s32)arg0);
    return 0;
}
