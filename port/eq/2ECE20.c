#include "common.h"

s32 func_002ECBA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/* Reads a0 and a1 only (the rest of the registers are not read by func_002ECBA8). */
s32 func_002ECE20(s32 arg0, s32 arg1) {
    s32 sp[68];

    func_002ECBA8(arg0, arg1, (s32)sp, (s32)&sp[64], (s32)&sp[65], (s32)&sp[66], (s32)&sp[67]);
    return sp[67];
}
