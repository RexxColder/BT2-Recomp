#include "common.h"

void func_00300790(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002FFCF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00300798(void);

s32 func_002FFC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0;

    func_00300790(arg0, arg1, arg2, arg3, arg4);
    temp_s0 = func_002FFCF0(arg0, arg1, arg2, arg3, arg4);
    func_00300798();
    return temp_s0;
}
