#include "common.h"

s32 func_0010B080(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_0010BB80(s64 arg0);
void func_0010BCF8();
void func_0010BD00();
void func_0010BDF0();
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_00114130(s32 arg0, s32 arg1);

void func_0010FAC0(s32 arg0) {
    s32 s2;
    s32 s1;
    s32 s0;

    s2 = func_0010B080(arg0);
    s1 = func_0010B0A0(arg0);
    s0 = s1 + 0x1E0;
    func_00114130(s0, 1);
    func_0010BB80(0x53);
    func_00113430(*(s32 *)(s2 + 8), s0, 1, 0x2A00, 0x2C80, 0, 0);
    func_0010BCF8();
    func_0010BD00();
    func_00113430(*(s32 *)(s2 + 8), s1 + 0x480, 1, 0x2A00, 0x2C80, 0, 0);
    func_0010BDF0();
    func_0010BD00();
    func_00113430(*(s32 *)(s2 + 8), s1 + 0x540, 1, 0x2A00, 0x2C80, 0, 0);
    func_0010BDF0();
}
