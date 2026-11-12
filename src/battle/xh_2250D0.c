#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(s32);                          /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

// Battle char setup: SetChara 0x19D, two flag sets, zeroes BtlChar_GetPos fields 0xC0/0xC4.
void func_002250D0(s32 arg0) {
    BattleSide_SetChara(arg0, 0x19D);
    func_002113C0(arg0, 9, 0x01000000, 1);
    func_002113C0(arg0, 1, 0x20000, 1);
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC0) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC4) = 0;
}
