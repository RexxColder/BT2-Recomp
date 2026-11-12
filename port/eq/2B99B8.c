#include "common.h"

void Rand_Range(void *arg0);
s32 func_002B8280(s32 arg0);
s32 func_002B9408(s32 arg0);
void func_002B9430(s32 arg0, void *arg1, void *arg2);
void func_002D7B80(s32 arg0, void *arg1, void *arg2);
extern u8 D_00379558[] __attribute__((section(".data")));
extern u8 D_00379588[] __attribute__((section(".data")));

void func_002B99B8(s32 arg0, void *arg1, void *arg2) {
    s32 sp[40];
    s32 temp_s0;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_00379558);
        return;
    }
    if (*(s32 *)arg1 == 0) {
        Rand_Range(D_00379588);
        return;
    }
    temp_s0 = func_002B9408(arg0);
    func_002B9430(arg0, arg1, sp);
    func_002D7B80(temp_s0, sp, arg2);
}
