#include "m2c_macros.h"

extern void *D_0042A570 __attribute__((section(".data")));

void func_003F0AA0(s32 arg0) {
    s32 mask = 0x40 << arg0;
    s32 v0 = M2C_FIELD(D_0042A570, s32 *, 0x218);

    if (!(v0 & mask)) {
        if (M2C_FIELD(D_0042A570, s32 *, 0x210) == arg0) {
            M2C_FIELD(D_0042A570, s32 *, 0x36B8) = 5;
        }
    } else {
        M2C_FIELD(D_0042A570, s32 *, 0x218) = v0 ^ mask;
    }
    M2C_FIELD(D_0042A570, s32 *, 0x218) |= 1 << arg0;
}
