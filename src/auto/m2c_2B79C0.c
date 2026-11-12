#include "m2c_macros.h"

M2C_UNK memcpy(M2C_UNK, s32, M2C_UNK);              /* extern */

s32 func_002B79C0(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    memcpy(arg2, arg0 + 0x70000000, arg1);
    return 0;
}
