#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002BD1D0(s32 arg0);
s32 Rand_Range(void *arg0);
extern u8 D_00379FB0[] __attribute__((section(".data")));

/* 0x002BD1E8(arg0): when func_002B8280(arg0) == 1, returns func_002BD1D0(arg0) != 1; otherwise Rand_Range(&D_00379FB0)
 * and returns 0. */
s32 func_002BD1E8(s32 arg0) {
    s32 r;

    r = func_002B8280(arg0);
    if (r == 1) {
        return func_002BD1D0(arg0) != r;
    }
    Rand_Range(D_00379FB0);
    return 0;
}
