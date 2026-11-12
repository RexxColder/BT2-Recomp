#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00347A30 __attribute__((section(".data")));

void func_002E0CD8(void) {
    memset(&D_00347A30, 0, 0x128);
    M2C_FIELD(&D_00347A30, s32 *, 4) = 8;
}
