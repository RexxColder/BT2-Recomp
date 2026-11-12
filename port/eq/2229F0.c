#include "common.h"

extern s32 func_00218838(s32 a0, s32 a1);
extern void BattleSide_SetChara(s32 a0, s32 a1);
extern s32 func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 *BtlChar_GetPos(s32 a0);
extern void func_00212DD8(s32 a0, s32 a1);
extern s32 func_0020FC38(s32 a0, s32 a1);

s32 func_002229F0(s32 obj) {
    if (func_00218838(obj, 0) != 0) {
        BattleSide_SetChara(obj, 0xD9);
    } else {
        BattleSide_SetChara(obj, 0xD7);
    }
    func_002113C0(obj, 0, 2, 0);
    *(s32 *)(BtlChar_GetPos(obj) + 0xC0) = 0;
    func_00212DD8(obj, 0);
    return func_0020FC38(obj, 0x32);
}
