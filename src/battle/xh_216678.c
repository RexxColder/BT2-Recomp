#include "m2c_macros.h"

M2C_UNK BtlMove_BrakeVertical(s32);                 /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_00216770(s32);                         /* extern */

// If func_00211310(arg0,0,2) is set, calls BtlMove_BrakeVertical(arg0); otherwise func_00216770(arg0).
void func_00216678(s32 arg0) {
    if (func_00211310(arg0, 0, 2) != 0) {
        BtlMove_BrakeVertical(arg0);
        return;
    }
    func_00216770(arg0);
}
