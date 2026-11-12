#include "m2c_macros.h"

extern void *D_0042BB78 __attribute__((section(".data")));

void func_0040AF10(s32 arg0) {
    s32 mask = 0x40 << arg0;
    s32 v0 = M2C_FIELD(D_0042BB78, s32 *, 0x240);

    if (!(v0 & mask)) {
        if (M2C_FIELD(D_0042BB78, s32 *, 0x23C) == arg0) {
            M2C_FIELD(D_0042BB78, s32 *, 0x37C4) = 5;
        }
    } else {
        M2C_FIELD(D_0042BB78, s32 *, 0x240) = v0 ^ mask;
    }
    M2C_FIELD(D_0042BB78, s32 *, 0x240) |= 1 << arg0;
}
