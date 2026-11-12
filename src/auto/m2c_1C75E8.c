#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern s32 D_003878A4;

void func_001C75E8(void *arg0, void *arg1) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s1, 0, 0x70);
    M2C_FIELD(temp_s1, s64 *, 0x50) = (s64) M2C_FIELD(arg1, s64 *, 0);
    M2C_FIELD(temp_s1, s64 *, 0x58) = (s64) M2C_FIELD(arg1, s64 *, 8);
    M2C_FIELD(temp_s1, s64 *, 0x60) = (s64) M2C_FIELD(arg1, s64 *, 0x10);
    M2C_FIELD(temp_s1, s64 *, 0x68) = (s64) M2C_FIELD(arg1, s64 *, 0x18);
    M2C_FIELD(temp_s1, s32 *, 0) = (s32) (D_003878A4 + 8);
}
