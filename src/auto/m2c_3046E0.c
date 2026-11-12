#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
M2C_UNK func_00303B80();                            /* extern */
M2C_UNK func_00304710();                            /* extern */

void func_003046E0(void) {
    PauseMenu_Term();
    func_00304710();
    BtlSeq_Term();
    func_00303B80();
}
