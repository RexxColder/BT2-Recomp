#include "common.h"

extern s32 func_002B8280(s32 arg0);
extern s32 func_002B9408(s32 arg0);
extern s32 func_002D7188(s32 arg0);
extern s32 Rand_Range(void *arg0);
extern u8 D_003799F0[] __attribute__((section(".data")));

/* 0x002BA930: if func_002B8280(arg0) != 1, Rand_Range(&D_003799F0) and return 0; else tail-call
 * func_002D7188(func_002B9408(arg0)). */
s32 func_002BA930(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_003799F0);
        return 0;
    }
    return func_002D7188(func_002B9408(arg0));
}
