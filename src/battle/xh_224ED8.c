#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(void *);                       /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

// Battle char setup: SetChara 0x19B, two func_002113C0 flag sets, zeroes BtlChar_GetPos fields 0xC0/0xC4 and field 0xB74.
void func_00224ED8(void *arg0) {
    BattleSide_SetChara(arg0, 0x19B);
    func_002113C0(arg0, 9, 0x01000000, 1);
    func_002113C0(arg0, 1, 0x20000, 1);
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC0) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC4) = 0;
    M2C_FIELD(arg0, s32 *, 0xB74) = 0;
}
