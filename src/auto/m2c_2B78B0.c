#include "m2c_macros.h"

extern s32 D_00346BE0 __attribute__((section(".data")));

void func_002B78B0(s32 arg0) {
    if (arg0 == 0) {
        D_00346BE0 = 0;
        return;
    }
    D_00346BE0 = 1;
}
