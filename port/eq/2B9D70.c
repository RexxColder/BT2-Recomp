#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
void func_002D6D40(s32 arg0, s32 arg1, s32 arg2);
void func_002D6D68(s32 arg0, s32 arg1);
void Rand_Range(void *arg0);
extern u8 D_00379760[] __attribute__((section(".data")));

/* 0x002B9D70(a0, a1, a2, a3): if func_002B8280(a0) != 1: Rand_Range(&D_00379760) and return; else h = func_002B9408(a0),
 * func_002D6D40(h, a1, a2), func_002D6D68(h, a3). */
void func_002B9D70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 h;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_00379760);
        return;
    }
    h = func_002B9408(arg0);
    func_002D6D40(h, arg1, arg2);
    func_002D6D68(h, arg3);
}
