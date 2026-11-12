#include "common.h"

s32 func_002B8280(s32 arg0);
void Rand_Range();
s32 func_002B9408(s32 arg0);
s32 func_002D6EB0(s32 arg0);
extern u8 D_003797D0[] __attribute__((section(".data")));

/* 0x002B9E80: if func_002B8280(arg0) != 1: Rand_Range(&D_003797D0) and return 0; otherwise tail call
 * func_002D6EB0(func_002B9408(arg0)). */
s32 func_002B9E80(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range((s32)D_003797D0);
        return 0;
    }
    return func_002D6EB0(func_002B9408(arg0));
}
