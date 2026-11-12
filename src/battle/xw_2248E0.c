#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212DD8(s32 arg0, s32 arg1);

// Sets the chara of the side to 0xFF, then if func_00211310 is nonzero for slots 0 and 1, calls func_00212DD8 with 0x1E.
void func_002248E0(s32 arg0) {
    BattleSide_SetChara(arg0, 0xFF);
    if ((func_00211310(arg0, 0, 1) != 0) && (func_00211310(arg0, 1, 1) != 0)) {
        func_00212DD8(arg0, 0x1E);
    }
}
