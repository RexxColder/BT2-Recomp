#include "common.h"

s32 func_002D6B40(void);
void func_002D6B90(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D6C30(s32 arg0, s32 arg1, s32 arg2);
void func_002D6C40(s32 arg0);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D7248(void);
s32 func_002E0D20(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346EA0 __attribute__((section(".data")));
extern s32 D_0037ABF0 __attribute__((section(".data")));
extern s32 D_0037AC20 __attribute__((section(".data")));
extern s32 D_0037AC40 __attribute__((section(".data")));

s32 func_002D6A28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_002D6B40();
    if (temp_v0 == 0) {
        return 0;
    }
    if (func_002D6C30(arg1, arg2, arg3) != 1) {
        func_002D6C90(0, 0, (s32)&D_0037ABF0);
        return 0;
    }
    func_002D6B90(temp_v0, arg0, arg1);
    temp_v0_2 = func_002D7248();
    if (temp_v0_2 == 0) {
        func_002D6C90(0, 0, (s32)&D_0037AC20);
        func_002D6C40(temp_v0);
        return 0;
    }
    *(s32 *)(temp_v0 + 0x24) = temp_v0_2;
    temp_v0_3 = func_002E0D20(0, 0, (s32)&D_0037AC20);
    if (temp_v0_3 == 0) {
        func_002D6C90(0, 0, (s32)&D_0037AC40);
        func_002D6C40(temp_v0);
        return 0;
    }
    *(s32 *)(temp_v0 + 0x30) = temp_v0_3;
    D_00346EA0 += 1;
    return temp_v0;
}
