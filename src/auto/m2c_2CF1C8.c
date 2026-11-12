#include "m2c_macros.h"

M2C_UNK func_002BFE98(s32, M2C_UNK);                /* extern */
M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK);            /* extern */
s32 func_002C3210();                                /* extern */

void func_002CF1C8(s32 arg0, M2C_UNK arg1) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000139);
        return;
    }
    func_002BFE98(arg0, arg1);
}
