#include "m2c_macros.h"

M2C_UNK func_002D7B60(M2C_UNK);                     /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00347368 __attribute__((section(".data")));

void func_002D7200(void) {
    memset(&D_00347368, 0, 0x26C);
    M2C_FIELD(&D_00347368, s32 *, 8) = 8;
    func_002D7B60(0);
}
