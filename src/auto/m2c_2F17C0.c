#include "m2c_macros.h"

extern s32 D_00353F7C __attribute__((section(".data")));
extern s32 D_00353F80 __attribute__((section(".data")));

void func_002F17C0(s32 arg0) {
    D_00353F7C = 0x28 - arg0;
    D_00353F80 = arg0;
}
