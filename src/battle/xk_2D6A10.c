#include "m2c_macros.h"

extern M2C_UNK D_00346EA8 __attribute__((section(".data")));

void func_002D6A10(s32 arg0, s32 arg1) {
    M2C_FIELD(&D_00346EA8, s32 *, 0) = arg0;
    M2C_FIELD(&D_00346EA8, s32 *, 4) = arg1;
}
