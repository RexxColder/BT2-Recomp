#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_0021DA50(s32 arg0) {
    BattleSide_SetChara(arg0, 0x53);
    return func_002113C0(arg0, 0, 2, 1);
}
