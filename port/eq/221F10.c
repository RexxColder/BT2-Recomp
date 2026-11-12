#include "common.h"

s32 func_00218838(u8 *arg0, s32 arg1);
s32 func_00217490(u8 *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void *BtlChar_GetPos(u8 *arg0);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00221F10(u8 *arg0) {
    f32 x;
    s32 q;

    if (func_00218838(arg0, 1) != 0) {
        if (func_00217490(arg0) == 0x80) {
            BattleSide_SetChara(arg0, 0xD0);
        } else {
            BattleSide_SetChara(arg0, 0xCF);
        }
    } else if (func_00217490(arg0) == 0x80) {
        BattleSide_SetChara(arg0, 0xCD);
    } else {
        BattleSide_SetChara(arg0, 0xCC);
    }
    /* cvt.w.s (truncates toward zero) of the product; the integer bits are stored */
    x = *(f32 *)(arg0 + 0xB58) * 15.0f;
    q = (s32)x;
    *(s32 *)(arg0 + 0x8C0) = q;
    *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC4) = 0;
    func_002113C0(arg0, 0, 2, 0);
}
