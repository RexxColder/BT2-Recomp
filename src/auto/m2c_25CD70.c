#include "m2c_macros.h"

extern void *D_00387A40;

void func_0025CD70(s32 arg0) {
    M2C_FIELD(D_00387A40, s32 *, 0x38020) = (s32) (M2C_FIELD(D_00387A40, s32 *, 0x38020) & ~(1 << arg0));
}
