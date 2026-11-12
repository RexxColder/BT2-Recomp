#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
s32 func_00305F50(s32, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */

s32 func_00305EE8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_s0;

    PauseMenu_Term();
    temp_s0 = func_00305F50(arg0, arg1, arg2, arg3);
    BtlSeq_Term();
    return temp_s0;
}
