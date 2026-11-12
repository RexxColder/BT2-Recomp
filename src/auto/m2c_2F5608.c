#include "m2c_macros.h"

extern s32 D_00354ED0 __attribute__((section(".data")));
extern s32 D_00354ED4 __attribute__((section(".data")));

void func_002F5608(s32 arg0) {
    D_00354ED0 = arg0;
    D_00354ED4 = arg0;
}
