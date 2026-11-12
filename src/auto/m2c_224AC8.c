#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(void *, M2C_UNK);       /* extern */
void *BtlChar_GetPos(void *);                       /* extern */
s32 BtlParam_IsType2to4();                          /* extern */
f32 BtlUtil_WrapAngle(f32);                         /* extern */

void func_00224AC8(void *arg0) {
    if (BtlParam_IsType2to4(arg0) != 0) {
        BattleSide_SetChara(arg0, 0x198);
    } else {
        BattleSide_SetChara(arg0, 0x197);
    }
    M2C_FIELD(arg0, f32 *, 0x168) = BtlUtil_WrapAngle(M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xB4) - M2C_FIELD(arg0, f32 *, 0x150));
}
