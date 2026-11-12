#include "common.h"

/* 0x0022A130: BattleSide_SetChara(a0, 0x2F); func_002113C0(a0, 0, 2, 1); tail call func_0020FC38(a0, 0x31). */
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC38(s32 arg0, s32 arg1);

void func_0022A130(s32 a0) {
    BattleSide_SetChara(a0, 0x2F);
    func_002113C0(a0, 0, 2, 1);
    func_0020FC38(a0, 0x31);
}
