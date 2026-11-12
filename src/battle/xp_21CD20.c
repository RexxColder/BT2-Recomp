#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(s32, s32);               /* extern */
void *BtlChar_GetPos(s32);                          /* extern */
extern f32 D_00385D90;

void func_0021CD20(s32 arg0) {
    BattleSide_SetChara(arg0, 0x10E);
    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC0) = (f32) D_00385D90;
}
