#include "m2c_macros.h"

extern void *D_0042732C __attribute__((section(".data")));

void func_003DD0C0(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_0042732C, s32 *, 0x108);
    if (!(temp_v0 & 0x20)) {
        M2C_FIELD(D_0042732C, s32 *, 0x74C) = 5;
    } else {
        M2C_FIELD(D_0042732C, s32 *, 0x108) = temp_v0 ^ 0x20;
    }
    M2C_FIELD(D_0042732C, s32 *, 0x108) = M2C_FIELD(D_0042732C, s32 *, 0x108) | 0x10;
}
