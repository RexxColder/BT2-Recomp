#include "common.h"

s32 func_00307590(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00393E44 __attribute__((section(".data")));

void func_002BC2D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00307590(2, arg0, arg1, arg2, arg3);
    D_00393E44 = arg0;
}
