#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00356E98 __attribute__((section(".data")));

void func_002FF640(void) {
    memset(&D_00356E98, 0, 0x10);
}
