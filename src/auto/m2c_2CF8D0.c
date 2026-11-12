#include "m2c_macros.h"

M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002CCC70(s32);                         /* extern */
M2C_UNK func_002D05E8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_002CF8D0(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000153, 1);
        return;
    }
    func_002D05E8(arg0, 0x2F, 1);
    func_002CCC70(arg0);
}
