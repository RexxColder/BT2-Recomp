#include "m2c_macros.h"

M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK);            /* extern */
s32 func_002C3210();                                /* extern */

s32 func_002D0468(void *arg0) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000111);
    }
    return M2C_FIELD(arg0, s32 *, 0x48);
}
