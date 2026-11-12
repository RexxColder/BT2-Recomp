#include "common.h"

/* GUESS arity (5): every callee here receives a0..a3 and t0 as they came in. */
void func_002F33C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F1CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F33D8(void);

/* 0x002F1C48(a0..a3, t0): func_002F33C0(a0..a3, t0); func_002F1CB8(a0..a3, t0); then tail-call func_002F33D8 with no
 * arguments (the argument registers were clobbered by the second call). */
void func_002F1C48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_002F33C0(arg0, arg1, arg2, arg3, arg4);
    func_002F1CB8(arg0, arg1, arg2, arg3, arg4);
    func_002F33D8();
}
