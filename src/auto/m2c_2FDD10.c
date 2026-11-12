#include "m2c_macros.h"

extern u32 D_0035600C __attribute__((section(".data")));

void func_002FDD10(u32 arg0) {
    D_0035600C = arg0;
    if (arg0 >= 2U) {
        D_0035600C = 0;
    }
}
