#include "common.h"

void BattleSide_SetChara(s32 a0, s32 a1);
u8 *BtlChar_GetPos(s32 a0);
extern f32 D_00385D90;

/* 0x0021CD20: set chara 0x10E on side a0; store D_00385D90 at +0xC0 of its pos. */
void func_0021CD20(s32 a0) {
    BattleSide_SetChara(a0, 0x10E);
    *(f32 *)(BtlChar_GetPos(a0) + 0xC0) = D_00385D90;
}
