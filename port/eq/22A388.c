#include "common.h"

/* 0x0022A388: BattleSide_SetChara(a0, 0x1A5); func_002113C0(a0, 0, 2, 1); func_0020FC38(a0, 0x1F); tail func_00212DD8(a0, 0xD). */
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00212DD8(s32 arg0, s32 arg1);

s32 func_0022A388(s32 a0) {
    BattleSide_SetChara(a0, 0x1A5);
    func_002113C0(a0, 0, 2, 1);
    func_0020FC38(a0, 0x1F);
    return func_00212DD8(a0, 0xD);
}
