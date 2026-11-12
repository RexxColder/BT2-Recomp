#include "common.h"

s32 func_002FC1D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern s32 D_0035537C __attribute__((section(".data")));

void func_002FC278(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s8 b = (s8)arg0;

    func_002FC1D8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    D_0035537C = b;
}
