#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00360AC8 __attribute__((section(".data")));
extern M2C_UNK D_00360AD0 __attribute__((section(".data")));

void func_00304710(void) {
    s32 temp_v0;

    temp_v0 = D_00360AC8 - 1;
    D_00360AC8 = temp_v0;
    if (temp_v0 == 0) {
        memset(&D_00360AD0, 0, 0x4000);
    }
}
