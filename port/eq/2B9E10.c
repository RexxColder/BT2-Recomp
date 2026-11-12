#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
s32 func_002D6EA8(s32 arg0, s32 arg1);
s32 Rand_Range(void *arg0);
extern u8 D_00379798[] __attribute__((section(".data")));

/* 0x002B9E10(arg0, arg1): when func_002B8280(arg0) != 1 tail-calls Rand_Range(&D_00379798); otherwise tail-calls
 * func_002D6EA8(func_002B9408(arg0), arg1). Both tail calls return the callee's value. */
s32 func_002B9E10(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        return Rand_Range(D_00379798);
    }
    return func_002D6EA8(func_002B9408(arg0), arg1);
}
