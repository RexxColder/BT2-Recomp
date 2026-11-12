#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
s32 func_002D7130(s32 arg0, s32 arg1);
s32 Rand_Range(void *arg0);
extern u8 D_003799C0[] __attribute__((section(".data")));

/* 0x002BA8C0(arg0, arg1): when func_002B8280(arg0) != 1 tail-calls Rand_Range(&D_003799C0); otherwise tail-calls
 * func_002D7130(func_002B9408(arg0), arg1). */
s32 func_002BA8C0(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        return Rand_Range(D_003799C0);
    }
    return func_002D7130(func_002B9408(arg0), arg1);
}
