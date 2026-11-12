#include "m2c_macros.h"

extern s32 D_0035532C __attribute__((section(".data")));
extern s32 D_00355330 __attribute__((section(".data")));

void func_002FABF0(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        D_0035532C = 0;
        D_00355330 = 0;
        return;
    }
    D_0035532C = arg0;
    D_00355330 = arg1;
}
