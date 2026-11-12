#include "common.h"

s32 func_0010B0A0(s32 arg0, s32 arg1);
s32 func_0010CDD8(s32 arg0, s32 arg1);
void func_00112B28(s32 arg0);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_0020C638(s32 arg0);

void func_001103F0(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s0;
    s32 v;

    s1 = func_0010B0A0(arg0, arg1);
    v = func_0020C638(arg1);
    if (v < 0) {
        return;
    }
    s0 = func_0010CDD8(arg1, v);
    if (s0 == 0) {
        return;
    }
    func_00112B28(s0);
    func_00113430(s0, s1 + 0x120, 1, 0x2A00, 0x2C80, 0, 0);
}
