#include "common.h"

void func_002C0E10(s32 arg0, s32 arg1, s32 arg2);

void func_002C4BC0(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    u8 *temp_s0;

    temp_s0 = (u8 *)(arg0 + 0x1F74);
    temp_v0 = *(s32 *)(temp_s0 + 0x18);
    if (temp_v0 != 8) {
        func_002C0E10(arg0, temp_v0, arg1);
    }
    temp_a1 = *(s32 *)(temp_s0 + 0x14);
    if (temp_a1 != 8) {
        func_002C0E10(arg0, temp_a1, arg1);
    }
    temp_a1_2 = *(s32 *)(temp_s0 + 0x1C);
    if (temp_a1_2 != 8) {
        func_002C0E10(arg0, temp_a1_2, arg1);
    }
}
