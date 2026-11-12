#include "m2c_macros.h"

extern void *D_00428F4C __attribute__((section(".data")));

void func_003ECEE8(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00428F4C, s32 *, 0x174);
    if (!(temp_v0 & 0x80)) {
        M2C_FIELD(D_00428F4C, s32 *, 0x1EC) = 5;
    } else {
        M2C_FIELD(D_00428F4C, s32 *, 0x174) = temp_v0 ^ 0x80;
    }
    M2C_FIELD(D_00428F4C, s32 *, 0x174) = M2C_FIELD(D_00428F4C, s32 *, 0x174) | 0x40;
}
