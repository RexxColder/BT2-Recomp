#include "common.h"

void Rand_Range(void *arg0);
s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
void func_002B9430(s32 arg0, void *arg1, void *arg2);
void func_002D7C20(s32 arg0, void *arg1, void *arg2);
extern u8 D_003795B8[] __attribute__((section(".data")));
extern u8 D_003795E8[] __attribute__((section(".data")));

void func_002B9A68(s32 arg0, void *arg1, void *arg2) {
    s32 sp[40];
    s32 temp_s0;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_003795B8);
        return;
    }
    if (*(s32 *)arg1 == 0) {
        Rand_Range(D_003795E8);
        return;
    }
    temp_s0 = func_002B9408(arg0);
    func_002B9430(arg0, arg1, sp);
    func_002D7C20(temp_s0, sp, arg2);
}
