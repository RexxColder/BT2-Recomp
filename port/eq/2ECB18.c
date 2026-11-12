#include "common.h"

void func_002ED118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_002ECBA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6);
void func_002ED130(void);

/* 0x002ECB18 ADXF_GetFnameRangeEx(a0..a5): func_002ED118 with the six arguments; then func_002ECBA8 with the same
 * six arguments and a 16-byte scratch buffer on the stack as the seventh; then func_002ED130; returns the result
 * of func_002ECBA8. (GUESS: func_002ED130 gets no argument; the asm leaves a0 as the callee left it.) */
s32 ADXF_GetFnameRangeEx(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 buf[0x10];
    s32 r;

    func_002ED118(arg0, arg1, arg2, arg3, arg4, arg5);
    r = func_002ECBA8(arg0, arg1, arg2, arg3, arg4, arg5, buf);
    func_002ED130();
    return r;
}
