#include "common.h"

s32 Rand_Range(void *arg0);
void func_002B6BD0(void *arg0);
void func_002B7290(void *arg0, s32 arg1);
s32 func_002C1120(s32 arg0);
s32 func_002D0468(s32 arg0);
extern u8 D_00379EE0[] __attribute__((section(".data")));

/* 0x002BC920(p): if func_002D0468(p->+0x3C) == 3: func_002B6BD0(p); if byte +0x72 is 0, func_002B7290(p, 0);
 * if byte +0x70 is 1 and func_002C1120(p->+0x3C) != 0, Rand_Range(&D_00379EE0). */
void func_002BC920(u8 *arg0) {
    if (func_002D0468(*(s32 *)(arg0 + 0x3C)) == 3) {
        func_002B6BD0(arg0);
        if (*(s8 *)(arg0 + 0x72) == 0) {
            func_002B7290(arg0, 0);
        }
        if (*(s8 *)(arg0 + 0x70) == 1 && func_002C1120(*(s32 *)(arg0 + 0x3C)) != 0) {
            Rand_Range(D_00379EE0);
        }
    }
}
