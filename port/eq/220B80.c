#include "common.h"

extern f32 D_00385F54;
extern f32 D_00385F58;
extern f32 D_00385F5C;
extern f32 D_00385F60;
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
u8 *BtlChar_GetPos(u8 *arg0);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_00220B80(u8 *arg0) {
    u8 *pos;

    BattleSide_SetChara(arg0, 0xEB);
    BtlAnim_SetBlend(arg0, D_00385F54);
    pos = BtlChar_GetPos(arg0);
    *(f32 *)(pos + 0xC4) = (*(f32 *)(arg0 + 0xB58) * D_00385F58 + D_00385F5C) * D_00385F60;
    return func_002113C0(arg0, 0, 2, 0);
}
