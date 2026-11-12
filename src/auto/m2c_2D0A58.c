#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK, M2C_UNK);       /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002D0AD8(s32, M2C_UNK, M2C_UNK);       /* extern */

s32 func_002D0A58(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000117, arg2);
    }
    func_002D0AD8(arg0, arg1, arg2);
    return 0;
}
