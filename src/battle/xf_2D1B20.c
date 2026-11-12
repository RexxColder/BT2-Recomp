#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */
s32 func_002C3210();                                /* extern */
s32 func_002D07B0(s32, M2C_UNK);                    /* extern */
M2C_UNK func_002D1B88(s32);                         /* extern */

s32 func_002D1B20(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF00012A);
    }
    if (func_002D07B0(arg0, 0x47) == 1) {
        return 0;
    }
    func_002D1B88(arg0);
    return 0;
}
