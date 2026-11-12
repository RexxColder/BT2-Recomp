#include "common.h"

extern f32 D_003867D8;

void BattleSide_SetChara(u8 *arg0, s32 arg1);
extern u8 *BtlChar_GetPos();
extern s32 func_00206958();
void func_0020FC38(u8 *arg0, s32 arg1);
void BtlChar_SetSmallVibration(u8 *arg0, f32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0022FA10(u8 *obj) {
    BattleSide_SetChara(obj, 0x10C);
    *(s32 *)(BtlChar_GetPos(obj) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos(obj) + 0xC4) = 0;
    func_00206958(obj, 0x2000);
    func_0020FC38(obj, 0x20);
    BtlChar_SetSmallVibration(obj, D_003867D8);
    func_002113C0(obj, 0, 2, 1);
}
