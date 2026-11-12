#include "common.h"

extern s32 Rand_Range(void *arg0);
extern s32 func_002B45D8(u8 *arg0);
extern s32 func_002B9FC0(u8 *arg0);
extern s32 func_00304760(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00379878[] __attribute__((section(".data")));

/* 0x002B9FE8: if func_002B9FC0(arg0 + 8) == 1, call func_00304760(arg0->+0x180, arg0->+0x184, 0); when that is 0,
 * Rand_Range(&D_00379878) and func_002B45D8(arg0) and return 0, else return its result. Otherwise return 0. */
s32 func_002B9FE8(u8 *arg0) {
    s32 result;

    if (func_002B9FC0(arg0 + 8) == 1) {
        result = func_00304760(*(s32 *)(arg0 + 0x180), *(s32 *)(arg0 + 0x184), 0);
        if (result == 0) {
            Rand_Range(D_00379878);
            func_002B45D8(arg0);
            return 0;
        }
        return result;
    }
    return 0;
}
