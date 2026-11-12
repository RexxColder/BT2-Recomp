#include "m2c_macros.h"

extern void *D_00387A40;

void func_001EDBD8(s32 arg0, s32 arg1) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(D_00387A40, s32 *, 8) + (arg0 * 0x1520);
    if (arg1 & 0xFF) {
        M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) | 2);
        return;
    }
    M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) & ~2);
}
