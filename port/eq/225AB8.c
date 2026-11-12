#include "common.h"

/* 0x00225AB8: BattleSide_SetChara(a0, 0x112); func_002113C0(a0, 0, 2, 0); tail call func_00212DD8(a0, 5). */
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212DD8(s32 arg0, s32 arg1);

s32 func_00225AB8(s32 a0) {
    BattleSide_SetChara(a0, 0x112);
    func_002113C0(a0, 0, 2, 0);
    return func_00212DD8(a0, 5);
}
