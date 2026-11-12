#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00217CB8(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0021C2A8(s32 arg0) {
    BattleSide_SetChara(arg0, 0x79);
    func_00217CB8(arg0);
    func_002113C0(arg0, 0, 2, 1);
}
