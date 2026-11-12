#include "m2c_macros.h"

extern void *D_00387F2C;

void func_002984E0(s32 arg0) {
    s32 temp_a0;

    M2C_FIELD(D_00387F2C, s32 *, 0x283C) = (s32) (M2C_FIELD(D_00387F2C, s32 *, 0x283C) + arg0);
    temp_a0 = M2C_FIELD(D_00387F2C, s32 *, 0x283C);
    if (temp_a0 > 0x98967F) {
        M2C_FIELD(D_00387F2C, s32 *, 0x283C) = 0x98967F;
        return;
    }
    if (temp_a0 < 0) {
        M2C_FIELD(D_00387F2C, s32 *, 0x283C) = 0;
    }
}
