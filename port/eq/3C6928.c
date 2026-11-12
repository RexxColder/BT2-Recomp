#include "m2c_macros.h"

extern void *D_00423114 __attribute__((section(".data")));

void func_003C6928(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00423114, s32 *, 0x18C);
    if (!(temp_v0 & 0x40)) {
        M2C_FIELD(D_00423114, s32 *, 0x362C) = 5;
    } else {
        M2C_FIELD(D_00423114, s32 *, 0x18C) = temp_v0 ^ 0x40;
    }
    M2C_FIELD(D_00423114, s32 *, 0x18C) = M2C_FIELD(D_00423114, s32 *, 0x18C) | 1;
}
