#include "m2c_macros.h"

s32 func_00307378(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
extern s32 D_00393E40 __attribute__((section(".data")));

void func_002BC240(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    D_00393E40 = func_00307378(0, arg0, arg1, arg2);
}
