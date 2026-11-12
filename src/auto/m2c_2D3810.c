#include "m2c_macros.h"

extern s32 D_00346E84 __attribute__((section(".data")));
extern s32 D_00346E88 __attribute__((section(".data")));

void func_002D3810(s32 arg0, s32 arg1) {
    D_00346E88 = arg0;
    D_00346E84 = arg1;
}
