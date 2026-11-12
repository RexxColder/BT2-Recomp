#include "m2c_macros.h"

extern void *D_0042FD74 __attribute__((section(".data")));

void func_0041CF08(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_0042FD74, s32 *, 0x134);
    if (!(temp_v0 & 0x8)) {
        M2C_FIELD(D_0042FD74, s32 *, 0x140) = 5;
    } else {
        M2C_FIELD(D_0042FD74, s32 *, 0x134) = temp_v0 ^ 0x8;
    }
    M2C_FIELD(D_0042FD74, s32 *, 0x134) = M2C_FIELD(D_0042FD74, s32 *, 0x134) | 0x4;
}
