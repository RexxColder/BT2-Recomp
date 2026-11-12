#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
M2C_UNK func_00304B30(s32);                         /* extern */

void func_00304B00(s32 arg0) {
    PauseMenu_Term();
    func_00304B30(arg0);
    BtlSeq_Term();
}
