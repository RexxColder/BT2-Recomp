#include "m2c_macros.h"

M2C_UNK BtlFacade_BeginWait();                      /* extern */
M2C_UNK func_00306F10();                            /* extern */
M2C_UNK func_003074E0(s32, M2C_UNK);                /* extern */

void func_003074A0(s32 arg0, M2C_UNK arg1) {
    BtlFacade_BeginWait();
    func_003074E0(arg0, arg1);
    func_00306F10();
}
