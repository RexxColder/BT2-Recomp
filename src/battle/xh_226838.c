#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(s32);                          /* extern */
M2C_UNK func_00203888(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_00211418(s32, M2C_UNK);                /* extern */
s32 func_00240398(s32);                             /* extern */

// Battle char setup: SetChara 0x86, func_00203888 with func_00240398 result, zeroes BtlChar_GetPos 0xC0/0xC4, flag 0x8000.
void func_00226838(s32 arg0) {
    BattleSide_SetChara(arg0, 0x86);
    func_00203888(arg0, func_00240398(arg0), 0);
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC0) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0xC4) = 0;
    func_00211418(arg0, 0x8000);
}
