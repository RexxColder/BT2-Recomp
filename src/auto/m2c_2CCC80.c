#include "m2c_macros.h"

M2C_UNK func_002BF4E8(s32, M2C_UNK);                /* extern */
s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002D2740(s32, M2C_UNK);                /* extern */

s32 func_002CCC80(s32 arg0, M2C_UNK arg1) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000144);
    }
    func_002D2740(arg0, arg1);
    func_002BF4E8(arg0, arg1);
    return 0;
}
