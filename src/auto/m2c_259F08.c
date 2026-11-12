#include "m2c_macros.h"

extern void *D_00387A10;

void func_00259F08(s32 arg0, s32 arg1) {
    M2C_FIELD(D_00387A10, s32 *, 0xB0) = arg0;
    M2C_FIELD(D_00387A10, s32 *, 0xB4) = arg1;
}
