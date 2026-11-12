#include "m2c_macros.h"

extern s32 D_00346BE0 __attribute__((section(".data")));
extern s32 D_00346BE4 __attribute__((section(".data")));
extern s32 D_00346BE8 __attribute__((section(".data")));
extern s32 D_00346BEC __attribute__((section(".data")));

void func_002B7938(void) {
    D_00346BE0 = 1;
    D_00346BE4 = 0;
    D_00346BE8 = 0;
    D_00346BEC = 0;
}
