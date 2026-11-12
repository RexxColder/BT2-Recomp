#include "common.h"

s32 func_002B8280(s32 arg0);
void func_002B9408(s32 arg0);
void Rand_Range();
extern u8 D_003796E8[] __attribute__((section(".data")));

/* 0x002B9C50: if func_002B8280(arg0) != 1: Rand_Range(&D_003796E8) (GUESS arity: the asm sets no second argument)
 * and return 0; otherwise func_002B9408(arg0) and return arg0->0x4C. */
s32 func_002B9C50(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range((s32)D_003796E8);
        return 0;
    }
    func_002B9408(arg0);
    return *(s32 *)(arg0 + 0x4C);
}
