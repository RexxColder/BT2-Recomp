#include "m2c_macros.h"

M2C_UNK memcpy(s32, s32, M2C_UNK);                  /* extern */

s32 func_002B7AA0(s32 arg0, M2C_UNK arg1, s32 arg2) {
    memcpy(arg2 + 0x70000000, arg0, arg1);
    return 0;
}
