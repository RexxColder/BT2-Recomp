#include "common.h"

s32 func_002ECBA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/* Reads a0..a3 and t0 only (func_002ECBA8 reads a0..a3, t0..t2 and no float register). */
s32 func_002ECAE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[2];

    return func_002ECBA8(arg0, arg1, arg2, (s32)&sp[0], arg3, arg4, (s32)&sp[1]);
}
