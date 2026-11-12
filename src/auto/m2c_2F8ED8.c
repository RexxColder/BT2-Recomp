#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_002F8ED8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    memset(arg0 + 0x28, 0, 8);
}
