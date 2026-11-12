#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
M2C_UNK func_00304190(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_00304130(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    PauseMenu_Term();
    func_00304190(arg0, arg1, arg2, arg3);
    BtlSeq_Term();
}
