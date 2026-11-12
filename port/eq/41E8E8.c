#include "m2c_macros.h"

extern void *D_0042FD74 __attribute__((section(".data")));

void func_0041E8E8(void) {
    s32 temp_a0;

    M2C_FIELD(D_0042FD74, s32 *, 0x1B4) = (s32) (M2C_FIELD(D_0042FD74, s32 *, 0x1AC) - 1);
    temp_a0 = M2C_FIELD(D_0042FD74, s32 *, 0x1B4);
    if (temp_a0 < 0) {
        M2C_FIELD(D_0042FD74, s32 *, 0x1B4) = (s32) (temp_a0 + M2C_FIELD(D_0042FD74, s32 *, 0x1B0));
    }
}
