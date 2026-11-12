#include "m2c_macros.h"

extern void *D_00387DA0;

s32 func_0029C830(void) {
    return ((s32) M2C_FIELD(D_00387DA0, s32 *, 0x54) >> 1) & 1;
}
