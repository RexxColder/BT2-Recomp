#include "m2c_macros.h"

extern s32 D_00356FE8 __attribute__((section(".data")));
extern s32 D_00356FEC __attribute__((section(".data")));

void func_003007D0(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        D_00356FE8 = 0;
        D_00356FEC = 0;
        return;
    }
    D_00356FE8 = arg0;
    D_00356FEC = arg1;
}
