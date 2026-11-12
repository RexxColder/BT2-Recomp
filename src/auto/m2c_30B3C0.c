#include "m2c_macros.h"

extern s32 D_00367C2C __attribute__((section(".data")));
extern s32 D_00367C30 __attribute__((section(".data")));

void func_0030B3C0(s32 arg0, s32 arg1) {
    D_00367C2C = arg0;
    D_00367C30 = arg1;
}
