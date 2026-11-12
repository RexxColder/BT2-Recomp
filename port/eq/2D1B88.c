#include "common.h"

void func_002D10D0(s32 arg0, s32 arg1);
void func_002D15A8(s32 arg0, s32 arg1, s32 arg2);

void func_002D1B88(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 temp_s0;

    temp_s0 = arg0 + 0xD30;
    func_002D15A8(arg0, (s32)&sp0, (s32)&sp4);
    if (*(s32 *)(temp_s0 + 0x28C) != sp0 || *(s32 *)(temp_s0 + 0x290) != sp4) {
        func_002D10D0(arg0, temp_s0);
        *(s32 *)(temp_s0 + 0x28C) = sp0;
        *(s32 *)(temp_s0 + 0x290) = sp4;
    }
    *(s32 *)(arg0 + 0x44) = 1;
}
