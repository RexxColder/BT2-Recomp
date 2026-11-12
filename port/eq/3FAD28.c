#include "m2c_macros.h"

s32 func_26E9E8(s32);
extern s32 D_0042A584 __attribute__((section(".data")));

void func_003FAD28(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_26E9E8(D_0042A584 + (0x28 * i) + 0x14);
    }
}
