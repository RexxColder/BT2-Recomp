#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK BtlAnim_SetBlend(f32, void *);              /* extern */
void *BtlChar_GetPos(void *);                       /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern f32 D_00385F54;
extern f32 D_00385F58;
extern f32 D_00385F5C;
extern f32 D_00385F60;

// Battle char setup: SetChara 0xEB, SetBlend with D_00385F54, field 0xC4 of BtlChar_GetPos from 0xB58 and float constants, one flag set.
void func_00220B80(void *arg0) {
    BattleSide_SetChara(arg0, 0xEB);
    BtlAnim_SetBlend(D_00385F54, arg0);
    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC4) = (f32) (((M2C_FIELD(arg0, f32 *, 0xB58) * D_00385F58) + D_00385F5C) * D_00385F60);
    func_002113C0(arg0, 0, 2, 0);
}
