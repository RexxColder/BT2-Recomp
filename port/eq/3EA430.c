#include "m2c_macros.h"

extern void *D_00428F48 __attribute__((section(".data")));

void func_003EA430(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00428F48, s32 *, 0x194);
    if (!(temp_v0 & 0x40)) {
        M2C_FIELD(D_00428F48, s32 *, 0x1B8) = 5;
    } else {
        M2C_FIELD(D_00428F48, s32 *, 0x194) = temp_v0 ^ 0x40;
    }
    M2C_FIELD(D_00428F48, s32 *, 0x194) = M2C_FIELD(D_00428F48, s32 *, 0x194) | 0x20;
}
