#include "m2c_macros.h"

extern void *D_0042BB80 __attribute__((section(".data")));

void func_00419E28(void) {
    s32 temp_a0;

    M2C_FIELD(D_0042BB80, s32 *, 0xDC) = (s32) (M2C_FIELD(D_0042BB80, s32 *, 0xD4) - 3);
    temp_a0 = M2C_FIELD(D_0042BB80, s32 *, 0xDC);
    if (temp_a0 < 0) {
        M2C_FIELD(D_0042BB80, s32 *, 0xDC) = (s32) (temp_a0 + M2C_FIELD(D_0042BB80, s32 *, 0x13C));
    }
    M2C_FIELD(D_0042BB80, s32 *, 0xD0) = (s32) (M2C_FIELD(D_0042BB80, s32 *, 0xD0) | 4);
    M2C_FIELD(D_0042BB80, s32 *, 0xC8) = 0x14;
}
