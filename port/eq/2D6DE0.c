#include "common.h"

void func_002D7330(s32 arg0, s32 arg1, s32 arg2);
s32 func_003063E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_0037AC60[] __attribute__((section(".data")));
extern u8 D_0037AC68[] __attribute__((section(".data")));

void func_002D6DE0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 temp_s0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x14;
    *(s32 *)(temp_s1 + 4) = arg1;
    *(s32 *)(temp_s1 + 8) = arg2;
    temp_s0 = *(s32 *)(arg0 + 0x24);
    sp[0] = arg1;
    sp[1] = arg2;
    if (func_003063E8((s32)sp, (s32)D_0037AC60, (s32)D_0037AC68, (s32)&sp[4]) == 0) {
        func_002D7330(temp_s0, 0, 0);
    } else {
        func_002D7330(temp_s0, sp[4], sp[5]);
    }
    *(s32 *)(arg0 + 0x14) = 1;
}
