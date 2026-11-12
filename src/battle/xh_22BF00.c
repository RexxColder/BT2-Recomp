#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK func_0020FC38(s32, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00211418(s32, M2C_UNK);                /* extern */

// Battle char setup: SetChara 0x37, one flag set, func_0020FC38 0x18, func_00211418 8.
void func_0022BF00(s32 arg0) {
    BattleSide_SetChara(arg0, 0x37);
    func_002113C0(arg0, 0, 2, 1);
    func_0020FC38(arg0, 0x18);
    func_00211418(arg0, 8);
}
