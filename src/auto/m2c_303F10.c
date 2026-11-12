#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
s32 func_00303F48(s32);                             /* extern */

s32 func_00303F10(s32 arg0) {
    s32 temp_s0;

    PauseMenu_Term();
    temp_s0 = func_00303F48(arg0);
    BtlSeq_Term();
    return temp_s0;
}
