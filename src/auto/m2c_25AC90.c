#include "m2c_macros.h"

extern void *D_00387A30;

void func_0025AC90(s32 arg0) {
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        M2C_FIELD(D_00387A30, s32 *, 0x2F4) = arg0;
        M2C_FIELD(D_00387A30, s32 *, 0x2F0) = 0;
    }
}
