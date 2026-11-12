#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
void func_002D6D50(s32 arg0, s32 arg1, s32 arg2);
s32 Rand_Range(void *arg0);
extern u8 D_00379720[] __attribute__((section(".data")));

/* 0x002B9CC0(arg0, arg1, arg2): when func_002B8280(arg0) != 1, Rand_Range(&D_00379720) (tail, result returned);
 * otherwise tail-calls func_002D6D50(func_002B9408(arg0), arg1, arg2). */
s32 func_002B9CC0(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002B8280(arg0) != 1) {
        return Rand_Range(D_00379720);
    }
    func_002D6D50(func_002B9408(arg0), arg1, arg2);
    return 0;
}
