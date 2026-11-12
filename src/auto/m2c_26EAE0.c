#include "m2c_macros.h"

void func_0026EAE0(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 1);
    M2C_FIELD(arg0, u32 *, 8) = (u32) (0x3CU / arg1);
}
