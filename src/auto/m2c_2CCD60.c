#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK, M2C_UNK);       /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002D04A8(s32, M2C_UNK, M2C_UNK);       /* extern */

s32 func_002CCD60(s32 arg0, M2C_UNK arg1) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000146, arg1);
    }
    func_002D04A8(arg0, 0x1D, arg1);
    return 0;
}
