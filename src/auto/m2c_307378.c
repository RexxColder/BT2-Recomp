#include "m2c_macros.h"

M2C_UNK BtlFacade_BeginWait();                      /* extern */
M2C_UNK func_00306F10();                            /* extern */
s32 func_003073E0(s32, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */

s32 func_00307378(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_s0;

    BtlFacade_BeginWait();
    temp_s0 = func_003073E0(arg0, arg1, arg2, arg3);
    func_00306F10();
    return temp_s0;
}
