#include "common.h"

/* 0x0022EBF8: SetChara(a0, func_00218838(a0, 0) ? 0xD6 : 0xD5); tail return func_002113C0(a0, 0, 2, 0). */
s32 func_00218838(s32 arg0, s32 arg1);
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_0022EBF8(s32 a0) {
    s32 r;

    r = func_00218838(a0, 0);
    BattleSide_SetChara(a0, (r == 0) ? 0xD5 : 0xD6);
    return func_002113C0(a0, 0, 2, 0);
}
