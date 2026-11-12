#include "common.h"

s32 func_00218838(s32 arg0, s32 arg1);
void BattleSide_SetChara(s32 arg0, s32 arg1);

void func_00223040(s32 arg0) {
    s32 v0 = func_00218838(arg0, 0);

    BattleSide_SetChara(arg0, (v0 == 0) ? 0xE3 : 0xE4);
}
