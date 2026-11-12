#include "m2c_macros.h"

extern s32 D_00356FDC __attribute__((section(".data")));
extern s32 D_00356FE0 __attribute__((section(".data")));
extern s32 D_00356FE4 __attribute__((section(".data")));

void func_003006A8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        D_00356FDC = 0;
        D_00356FE0 = 0;
        D_00356FE4 = 0;
        return;
    }
    D_00356FDC = arg0;
    D_00356FE0 = arg1;
    D_00356FE4 = arg2;
}
