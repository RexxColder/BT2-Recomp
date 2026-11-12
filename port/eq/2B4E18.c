#include "common.h"

s32 func_002B8280(void *arg0);
s32 Rand_Range(void *arg0, s32 arg1);
extern u8 D_00378380[] __attribute__((section(".data")));

void func_002B4E18(void *arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(D_00378380, arg1);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x54) = arg1;
}
