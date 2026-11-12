#include "common.h"

extern s32 func_00217490(s32 arg0);
extern void BattleSide_SetChara(s32 arg0, s32 arg1);
extern void func_0020FC38(s32 arg0, s32 arg1);

void func_0021A3E8(u8 *self) {
    if (func_00217490((s32)self) == 0x1B) {
        BattleSide_SetChara((s32)self, 0x51);
    } else {
        BattleSide_SetChara((s32)self, 0x50);
    }
    func_0020FC38((s32)self, 0x2E);
    *(s32 *)(self + 0x149C) = *(s32 *)(self + 0x149C) + 1;
}
