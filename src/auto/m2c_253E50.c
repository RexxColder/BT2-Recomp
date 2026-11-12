#include "m2c_macros.h"

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_003879D0;

void func_00253E50(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 * 0x14;
    memset(temp_s0 + D_003879D0 + 0x1A0, 0, 0x14);
    M2C_FIELD((temp_s0 + D_003879D0), s32 *, 0x1A0) = -1;
    M2C_FIELD((((0x12 - arg0) * 4) + D_003879D0), s32 *, 0x7C) = 0;
}
