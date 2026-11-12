#include "common.h"

s32 func_002EAC10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10);

/* t0/t1 (arg4/arg5) reach func_002EAC10 as its 9th/10th (stack) arguments */
s32 func_002EA958(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return func_002EAC10(arg0, 0, 0, arg1, arg2, 0, 0xFFFFF, arg3, arg4, arg5, 0);
}
