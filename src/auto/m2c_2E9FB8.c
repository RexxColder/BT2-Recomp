#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00348C50 __attribute__((section(".data")));
extern s32 D_00348C54 __attribute__((section(".data")));
extern M2C_UNK D_00348C58 __attribute__((section(".data")));

void func_002E9FB8(void) {
    memset(&D_00348C58, 0, 0x100);
    D_00348C50 = 0;
    D_00348C54 = 0;
}
