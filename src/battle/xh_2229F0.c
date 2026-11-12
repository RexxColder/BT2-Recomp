#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(s32);                          /* extern */
M2C_UNK func_0020FC38(s32, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00212DD8(s32, M2C_UNK);                /* extern */
s32 func_00218838(s32, M2C_UNK);                         /* extern */

// Battle char setup: SetChara 0xD9 or 0xD7 by func_00218838, one flag set, zeroes BtlChar_GetPos field 0xC0, func_00212DD8 0 and func_0020FC38 0x32.
void func_002229F0(s32 arg0) {
    if (func_00218838(arg0, 0) != 0) {
        BattleSide_SetChara(arg0, 0xD9);
    } else {
        BattleSide_SetChara(arg0, 0xD7);
    }
    func_002113C0(arg0, 0, 2, 0);
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC0) = 0;
    func_00212DD8(arg0, 0);
    func_0020FC38(arg0, 0x32);
}
