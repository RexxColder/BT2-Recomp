#include "common.h"

u8 *func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_0010C170(void);
void func_0010C298(void);
s32 func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);

s32 func_00119E90(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    u8 *temp_s2;

    temp_s2 = func_0010B080(arg0);
    temp_s1 = func_0010B0A0(arg0);
    temp_s0 = temp_s1 + 0x3BA0;
    func_00114130(temp_s0, 1);
    func_0010C170();
    func_00113430(*(s32 *)(temp_s2 + 0xC), temp_s0, 1, 0x2A00, 0x2C00, 0, 0);
    func_0010C298();
    return func_00113430(*(s32 *)(temp_s2 + 0xC), temp_s1 + 0x3CC0, 1, 0x2A00, 0x2C00, 0, 0);
}
