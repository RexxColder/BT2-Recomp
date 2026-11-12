#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK, M2C_UNK);       /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002D05E8(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_002D1C08(s32, s32, M2C_UNK);           /* extern */

s32 func_002D1920(s32 arg0, s32 arg1) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000123, 4);
    }
    func_002D1C08(arg0, arg1, 4);
    if (arg1 != 0) {
        func_002D05E8(arg0, 0xF, 4);
    }
    return 0;
}
