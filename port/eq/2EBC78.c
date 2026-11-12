#include "common.h"

void func_002E93C0(void);
void func_002E93D8(void);
s32 func_002F1ED0(s32 arg0);
void func_002F1F10(s32 arg0, s32 arg1);
void func_002F2078(s32 arg0, s32 arg1);
void func_002F21A0(s32 arg0);
void func_002F2280(s32 arg0, s32 arg1, s32 arg2);
void func_002F2C40(s32 arg0, s32 arg1);
void func_002F2E60(s32 arg0, s32 arg1);
void func_002F3040(s32 arg0, s32 arg1);

s32 func_002EBC78(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    if (func_002F1ED0(*(s32 *)(arg0 + 4)) != 1) {
        func_002F21A0(*(s32 *)(arg0 + 4));
    }
    func_002E93C0();
    temp_a2 = *(s32 *)(arg0 + 0x18);
    temp_v0 = *(s32 *)(arg0 + 0xC) - temp_a2;
    *(s32 *)(arg0 + 0x24) = 0;
    temp_v0_2 = (arg1 < temp_v0) ? arg1 : temp_v0;
    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x34) + temp_a2;
    *(s32 *)(arg0 + 0x20) = temp_v0_2;
    if (temp_v0_2 == 0) {
        *(s8 *)(arg0 + 1) = 3;
        var_s0 = 0;
    } else {
        func_002F2280(*(s32 *)(arg0 + 4), -1, temp_a2);
        func_002F3040(*(s32 *)(arg0 + 4), arg2);
        func_002F2C40(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 0x30));
        *(s8 *)(arg0 + 1) = 2;
        *(s8 *)(arg0 + 3) = 0;
        func_002F2E60(*(s32 *)(arg0 + 4), 0);
        func_002F1F10(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 0x18));
        func_002F2078(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 0x20));
        var_s0 = *(s32 *)(arg0 + 0x20);
    }
    func_002E93D8();
    return var_s0;
}
