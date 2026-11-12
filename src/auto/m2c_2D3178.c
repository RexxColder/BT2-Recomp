#include "m2c_macros.h"

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */

void func_002D3178(void *arg0) {
    memset(arg0 + 0x18, 0, 0xF0);
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x19C) = (s32) (M2C_FIELD(arg0, s32 *, 0x19C) + 1);
}
