#include "m2c_macros.h"

extern s32 D_003475D4 __attribute__((section(".data")));

void func_002D80E8(void) {
    if (D_003475D4 > 0) {
        D_003475D4 -= 1;
    }
}
