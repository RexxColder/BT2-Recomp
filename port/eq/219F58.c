#include "common.h"

s32 func_00217490(u8 *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_00217CB8(u8 *arg0);
void func_0020FC38(u8 *arg0, s32 arg1);

void func_00219F58(u8 *arg0) {
    if (func_00217490(arg0) == 0x1B) {
        BattleSide_SetChara(arg0, 0x4E);
    } else {
        BattleSide_SetChara(arg0, 0x4D);
    }
    func_00217CB8(arg0);
    func_0020FC38(arg0, 0x2E);
    *(s32 *)(arg0 + 0x149C) += 1;
}
