#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

s32 func_00211310(s32, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK func_00212DD8(s32, M2C_UNK);                /* extern */

// Sets battle side 0xFF; if func_00211310 flags 0 and 1 both set, calls func_00212DD8 with 0x1E.
void func_002248E0(s32 arg0) {
    BattleSide_SetChara(arg0, 0xFF);
    if ((func_00211310(arg0, 0, 1) != 0) && (func_00211310(arg0, 1, 1) != 0)) {
        func_00212DD8(arg0, 0x1E);
    }
}
