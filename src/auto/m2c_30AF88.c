#include "m2c_macros.h"

M2C_UNK BtlSeq_Term();                              /* extern */
M2C_UNK PauseMenu_Term();                           /* extern */

void func_0030AF88(s8 *arg0) {
    PauseMenu_Term();
    *arg0 = 0;
    BtlSeq_Term();
}
