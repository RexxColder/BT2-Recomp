#include "m2c_macros.h"

extern void *D_00387A40;

void func_00183B30(void *arg0, s32 arg1) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(D_00387A40, s32 *, 8) + (M2C_FIELD(arg0, s32 *, 0xB08) * 0x1520);
    if (arg1 & 0xFF) {
        M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) | 0x10);
        return;
    }
    M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) & ~0x10);
}
