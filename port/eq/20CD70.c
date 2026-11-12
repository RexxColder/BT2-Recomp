#include "common.h"

s32 func_00211288(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387930;

void func_0020CD70(s32 arg0) {
    if ((D_00387930 != 0) && ((u32)arg0 < 2U)) {
        func_002113C0(func_00211288(arg0), 7, 0x400, 1);
    }
}
