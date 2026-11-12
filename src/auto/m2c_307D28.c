#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00366528 __attribute__((section(".data")));
extern M2C_UNK D_00366530 __attribute__((section(".data")));

void func_00307D28(void) {
    s32 temp_v0;

    temp_v0 = D_00366528 - 1;
    D_00366528 = temp_v0;
    if (temp_v0 == 0) {
        memset(&D_00366530, 0, 0x300);
    }
}
