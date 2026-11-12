#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00217CB8(s32);                         /* extern */

// Battle char setup: SetChara 0x79, func_00217CB8, one flag set.
void func_0021C2A8(s32 arg0) {
    BattleSide_SetChara(arg0, 0x79);
    func_00217CB8(arg0);
    func_002113C0(arg0, 0, 2, 1);
}
