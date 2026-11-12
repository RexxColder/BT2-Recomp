#include "common.h"

/* 0x0022C0F0: BattleSide_SetChara(a0, 0x38); func_002113C0(a0, 0, 2, 1); func_0020FC38(a0, 0x1A); tail func_00211418(a0, 0x10). */
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC38(s32 arg0, s32 arg1);
void func_00211418(s32 arg0, s32 arg1);

void func_0022C0F0(s32 a0) {
    BattleSide_SetChara(a0, 0x38);
    func_002113C0(a0, 0, 2, 1);
    func_0020FC38(a0, 0x1A);
    func_00211418(a0, 0x10);
}
