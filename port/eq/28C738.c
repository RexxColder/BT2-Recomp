#include "common.h"

s32 func_0028CB60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* a0..a3, t0, t1 are not written before the jal: they are this function's parameters, passed through. */
s64 func_0028C738(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return (s64)(s32)func_0028CB60(arg0, arg1, arg2, arg3, arg4, arg5);
}
