#include "common.h"

extern s32 func_00217490(s32 arg0);
extern void BattleSide_SetChara(s32 arg0, s32 arg1);
extern void func_00217CB8(s32 arg0);

void func_0021D340(u8 *self) {
    if (func_00217490((s32)self) == 0x1B) {
        BattleSide_SetChara((s32)self, 0x54);
    } else {
        BattleSide_SetChara((s32)self, 0x53);
    }
    func_00217CB8((s32)self);
    *(s32 *)(self + 0x149C) = *(s32 *)(self + 0x149C) + 1;
}
