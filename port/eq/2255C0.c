#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_00212DD8(s32 arg0, s32 arg1);

s32 func_002255C0(s32 arg0) {
    BattleSide_SetChara(arg0, 0x113);
    return func_00212DD8(arg0, 5);
}
