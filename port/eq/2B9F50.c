#include "common.h"

extern s32 func_002B8280(s32 arg0);
extern s32 func_002B9408(s32 arg0);
extern s32 func_002D6EC0(s32 arg0);
extern s32 Rand_Range(void *arg0);
extern u8 D_00379840[] __attribute__((section(".data")));

/* 0x002B9F50: if func_002B8280(arg0) != 1, Rand_Range(&D_00379840) and return 0; else tail-call
 * func_002D6EC0(func_002B9408(arg0)). */
s32 func_002B9F50(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_00379840);
        return 0;
    }
    return func_002D6EC0(func_002B9408(arg0));
}
