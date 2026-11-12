#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(s32);                          /* extern */
M2C_UNK BtlChar_SetSmallVibration(f32, s32);        /* extern */
M2C_UNK func_00206958(s32, M2C_UNK);                /* extern */
M2C_UNK func_0020FC38(s32, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern f32 D_003867D8;

// Battle char setup: SetChara 0x10C, zeroes BtlChar_GetPos fields 0xC0/0xC4, func_00206958 0x2000, func_0020FC38 0x20, small vibration, one flag set.
void func_0022FA10(s32 arg0) {
    BattleSide_SetChara(arg0, 0x10C);
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC0) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC4) = 0;
    func_00206958(arg0, 0x2000);
    func_0020FC38(arg0, 0x20);
    BtlChar_SetSmallVibration(D_003867D8, arg0);
    func_002113C0(arg0, 0, 2, 1);
}
