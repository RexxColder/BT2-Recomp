#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(void *, s32, M2C_UNK, s32); /* extern */
extern void *gEftDust;

void func_001415D8(s32 arg0, M2C_UNK arg1) {
    s32 temp_a3;

    temp_a3 = M2C_FIELD(gEftDust, s32 *, 0x34);
    if ((M2C_FIELD(gEftDust, s32 *, 0x2C) + M2C_FIELD(gEftDust, s32 *, 0x30) + temp_a3) != 0) {
        EftTexSet_Keep32(gEftDust + 0xB0, arg0, arg1, temp_a3);
    }
}
