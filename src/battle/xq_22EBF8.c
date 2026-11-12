#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(s32, M2C_UNK);          /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_00218838(s32, M2C_UNK);                         /* extern */

void func_0022EBF8(s32 arg0) {
    BattleSide_SetChara(arg0, (func_00218838(arg0, 0) != 0) ? 0xD6 : 0xD5);
    func_002113C0(arg0, 0, 2, 0);
}
