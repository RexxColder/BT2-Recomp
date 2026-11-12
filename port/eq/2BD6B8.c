#include "common.h"

/* GUESS arity (5) for func_002F1DD8: the asm passes a0..a3 and t0 unchanged. */
void func_002F1DD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F1C48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F2280(s32 arg0, s32 arg1);

/* 0x002BD6B8(a0..a3, t0): func_002F1DD8(a0..a3, t0); func_002F1C48(a0..a3, t0); then tail-call
 * func_002F2280(a0, t0) (t0 as it came in). */
void func_002BD6B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_002F1DD8(arg0, arg1, arg2, arg3, arg4);
    func_002F1C48(arg0, arg1, arg2, arg3, arg4);
    func_002F2280(arg0, arg4);
}
