#include "m2c_macros.h"

extern void *D_00387A10;

void func_00259F20(s32 arg0) {
    M2C_FIELD(D_00387A10, s32 *, 0xB8) = arg0;
    M2C_FIELD(D_00387A10, s32 *, 0xAC) = (s32) (M2C_FIELD(D_00387A10, s32 *, 0xAC) | 1);
}
