#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00212DD8(s32, M2C_UNK);                /* extern */

// Battle char setup: SetChara 0x112, one flag set, func_00212DD8 with 5.
void func_00225AB8(s32 arg0) {
    BattleSide_SetChara(arg0, 0x112);
    func_002113C0(arg0, 0, 2, 0);
    func_00212DD8(arg0, 5);
}
