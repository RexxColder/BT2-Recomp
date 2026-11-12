#include "m2c_macros.h"

extern s32 D_00347BD8 __attribute__((section(".data")));
extern s32 D_00347BDC __attribute__((section(".data")));

s32 func_002E7020(s32 arg0, s32 arg1) {
    D_00347BD8 = arg0;
    D_00347BDC = arg1;
    return 0;
}
