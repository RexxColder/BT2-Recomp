#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */
M2C_UNK func_00303B80();                            /* extern */
M2C_UNK func_003054C0();                            /* extern */

void func_00305490(void) {
    PauseMenu_Term();
    func_003054C0();
    BtlSeq_Term();
    func_00303B80();
}
