#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
s32 func_003047B8(s32, M2C_UNK, M2C_UNK);           /* extern */

s32 func_00304760(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;

    PauseMenu_Term();
    temp_s0 = func_003047B8(arg0, arg1, arg2);
    BtlSeq_Term();
    return temp_s0;
}
