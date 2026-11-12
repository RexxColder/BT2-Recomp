#include "m2c_macros.h"

M2C_UNK _setlocale_r(s32, s32, M2C_UNK);            /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

void func_0032B680(s32 arg0, M2C_UNK arg1) {
    _setlocale_r(D_0036A600, arg0, arg1);
}
