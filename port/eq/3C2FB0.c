#include "m2c_macros.h"

extern void *D_00421CF4 __attribute__((section(".data")));

void func_003C2FB0(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00421CF4, s32 *, 0x1FC);
    if (!(temp_v0 & 0x80)) {
        M2C_FIELD(D_00421CF4, s32 *, 0x678) = 5;
    } else {
        M2C_FIELD(D_00421CF4, s32 *, 0x1FC) = temp_v0 ^ 0x80;
    }
    M2C_FIELD(D_00421CF4, s32 *, 0x1FC) = M2C_FIELD(D_00421CF4, s32 *, 0x1FC) | 0x40;
}
