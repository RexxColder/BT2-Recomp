#include "common.h"

void func_002D8710(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002B5620(s32 arg0_unused, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_a0;
    s32 temp_a1;
    s32 sp0;
    s32 sp4;

    temp_v0 = *(s32 *)(arg1 + 0x38);
    temp_a1 = *(s32 *)(temp_v0 + 4);
    temp_a0 = *(s32 *)(temp_v0 + 0);
    sp0 = 0;
    sp4 = 0;
    *(s32 *)(arg2 + 0x88) = 0;
    *(s32 *)(arg2 + 0x8C) = 0;
    if (temp_a0 != 0) {
        if (temp_a1 >= 5) {
            func_002D8710(temp_a0 + 4, temp_a1 - 4, (s32)&sp0, (s32)&sp4);
        }
    }
    if (sp0 != 0 && sp4 > 0) {
        *(s32 *)(arg2 + 0x8C) = sp4;
        *(s32 *)(arg2 + 0x88) = sp0;
    }
}
