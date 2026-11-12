#include "common.h"

s32 func_002B7CB8(s32 arg0);
s32 func_002B8280(s32 arg0);
void Rand_Range(void *arg0);
void func_002CAE98(s32 arg0, s32 *arg1, s32 *arg2);
extern u8 D_003785C0[] __attribute__((section(".data")));

void func_002B5A18(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 temp_v0;
    s32 temp_v0_2;

    *arg1 = 0;
    *arg2 = 0;
    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_003785C0);
        return;
    }
    temp_v0 = func_002B7CB8(arg0);
    if (temp_v0 != 0) {
        func_002CAE98(temp_v0, arg1, arg2);
        temp_v0_2 = *arg2;
        if (temp_v0_2 >= 4) {
            *arg2 = temp_v0_2 - 4;
            *arg1 += 4;
        }
    }
}
