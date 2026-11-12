#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
s32 func_00305998(s32, M2C_UNK);                    /* extern */

s32 func_00305950(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    PauseMenu_Term();
    temp_s0 = func_00305998(arg0, arg1);
    BtlSeq_Term();
    return temp_s0;
}
