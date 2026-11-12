#include "common.h"

s32 func_002D7B70(s32 arg0);
void func_002D6C90(s32 arg0, s32 arg1, u8 *arg2);
extern u8 D_0037ACB0[] __attribute__((section(".data")));

void func_002D78A8(s32 arg0, u32 *arg1, s16 *arg2) {
    s32 i;

    if (func_002D7B70(arg0) != 1) {
        func_002D6C90(0, 0, D_0037ACB0);
        return;
    }
    for (i = 0; i < 0x100; i++) {
        arg2[i] = (s16)(arg1[i] >> 0xF);
    }
}
