#include "m2c_macros.h"

extern s32 D_00388724 __attribute__((section(".data")));

void EftBurst_End(void) {
    D_00388724 = 1;
}
