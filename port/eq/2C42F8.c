#include "common.h"

/* GUESS arity: a0..a3 are not written before the first call, passed through (ctx says 0) */
s32 func_002C2318(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
/* 5th arg (t0) is incoming, passed through */
void func_002C53D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C4398(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C42F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[2];

    sp[0] = 0;
    if (func_002C2318(arg0, arg1, arg2, arg3, arg4) != 0) {
        func_002C53D0(arg0, arg1, arg2, arg3, (s32)sp);
        if (sp[0] != 0) {
            func_002C4398(arg0, 0, arg2 - 0x12, arg3 + 0x12);
        }
        return 1;
    }
    return func_002C4398(arg0, arg1, arg2, arg3);
}
