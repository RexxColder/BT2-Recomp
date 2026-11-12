#include "common.h"

void func_002D5B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_002D6840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x002D67C8(a0..a3, t0..t3): func_002D5B50(a0, a1, t0, t1, t2, t3); func_002D6840(a0, a1, a2, a3, 0); then the word
 * at a3 = 1. */
void func_002D67C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_002D5B50(arg0, arg1, arg4, arg5, arg6, arg7);
    func_002D6840(arg0, arg1, arg2, arg3, 0);
    *(s32 *)arg3 = 1;
}
