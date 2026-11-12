#include "common.h"

s32 func_002C3210(s32 arg0);
void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346E2C[] __attribute__((section(".data")));

void func_002D0560(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (func_002C3210(D_00346E2C[i]) == 0) {
            func_002D05E8(D_00346E2C[i], arg0, arg1);
        }
    }
}
