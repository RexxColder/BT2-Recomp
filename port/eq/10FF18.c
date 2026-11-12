#include "common.h"

s32 func_0010B0A0(s32 arg0);
void func_00112B28(s32 arg0);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern s32 *D_00387A40;

void func_0010FF18(s32 arg0, s32 arg1) {
    s32 s1;
    s32 t;
    s32 addr;

    s1 = func_0010B0A0(arg0);
    addr = arg1 * 0x18580 + *D_00387A40 + 0x58;
    t = *(s32 *)addr;
    if (t != 0) {
        func_00112B28(t);
        func_00113430(t, s1 + 0x960, 1, 0x2A00, 0x2C80, 0, 0);
    }
}
