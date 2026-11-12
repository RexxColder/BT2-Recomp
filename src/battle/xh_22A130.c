#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK func_0020FC38(s32, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

// Battle char setup: SetChara 0x2F, one flag set, func_0020FC38 with 0x31.
void func_0022A130(s32 arg0) {
    BattleSide_SetChara(arg0, 0x2F);
    func_002113C0(arg0, 0, 2, 1);
    func_0020FC38(arg0, 0x31);
}
