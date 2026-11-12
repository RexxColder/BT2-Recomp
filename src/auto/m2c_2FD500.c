#include "m2c_macros.h"

extern s32 D_00356004 __attribute__((section(".data")));
extern s32 D_00356008 __attribute__((section(".data")));

void func_002FD500(s32 arg0, s32 arg1) {
    D_00356004 = arg0;
    D_00356008 = arg1;
}
