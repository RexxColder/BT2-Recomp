#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK, M2C_UNK);       /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002D05E8(s32, M2C_UNK, M2C_UNK);       /* extern */

s32 func_002C1120(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000161, 1);
    }
    func_002D05E8(arg0, 0x31, 1);
    return 0;
}
