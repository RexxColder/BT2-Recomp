#include "common.h"

/* GUESS arity: the asm passes a0/a1 (arg0, arg1) through to func_002D8278; ctx.h says 0 */
s32 func_002D8278(s32 arg0, s32 arg1);
s32 strncmp(void *a, void *b, u32 n);
extern u8 D_0037AE58[] __attribute__((section(".data")));

s32 func_002D8340(s32 arg0, s32 arg1) {
    s32 ret;

    if (arg0 == 0 || arg1 < 0) {
        return 0;
    }
    ret = func_002D8278(arg0, arg1);
    if (ret != 0) {
        ret = strncmp((u8 *)arg0 + 0x14, D_0037AE58, 1) == 0;
    }
    return ret;
}
