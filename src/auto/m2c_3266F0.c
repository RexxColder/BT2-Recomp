#include "m2c_macros.h"

M2C_UNK _strtol_r(s32, s32, M2C_UNK, M2C_UNK);      /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

void func_003266F0(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    _strtol_r(D_0036A600, arg0, arg1, arg2);
}
