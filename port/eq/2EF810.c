#include "common.h"

extern s32 D_0039D6C8[] __attribute__((section(".data")));
extern s32 D_0039D6D0[] __attribute__((section(".data")));

void func_002EF810(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_0039D6C8[1] = arg1;
    D_0039D6C8[0] = arg0;
    D_0039D6D0[1] = arg3;
    D_0039D6D0[0] = arg2;
}
