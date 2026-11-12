#include "m2c_macros.h"

M2C_UNK func_002D6CD0(M2C_UNK);                     /* extern */
M2C_UNK func_002D8CD0();                            /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00346EA0 __attribute__((section(".data")));

void func_002D6970(void) {
    memset(&D_00346EA0, 0, 0x4C8);
    M2C_FIELD(&D_00346EA0, s32 *, 4) = 8;
    func_002D6CD0(1);
    func_002D8CD0();
}
