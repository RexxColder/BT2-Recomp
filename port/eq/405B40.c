#include "m2c_macros.h"

extern void *D_0042BB74 __attribute__((section(".data")));

void func_00405B40(s32 arg0) {
    s32 mask = 0x40 << arg0;
    s32 v0 = M2C_FIELD(D_0042BB74, s32 *, 0x210);

    if (!(v0 & mask)) {
        if (M2C_FIELD(D_0042BB74, s32 *, 0x20C) == arg0) {
            M2C_FIELD(D_0042BB74, s32 *, 0x36C0) = 5;
        }
    } else {
        M2C_FIELD(D_0042BB74, s32 *, 0x210) = v0 ^ mask;
    }
    M2C_FIELD(D_0042BB74, s32 *, 0x210) |= 1 << arg0;
}
