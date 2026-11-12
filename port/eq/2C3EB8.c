#include "common.h"

s32 func_002C4470(s32 arg0, s32 arg1, s32 arg2);

/* 0x002C3EB8(a0, cb, d0, d1, t0, t1): r = func_002C4470(a0, t0, t1). When r == 1 and cb != 0, calls cb(d0, d1).
 * Returns r. */
s32 func_002C3EB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 r;

    r = func_002C4470(arg0, arg4, arg5);
    if (r == 1 && arg1 != 0) {
        ((s32 (*)(s32, s32))arg1)(arg2, arg3);
    }
    return r;
}
