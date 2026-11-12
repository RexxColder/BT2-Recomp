#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00217CB8(s32 arg0);

void func_0021AC68(u8 *arg0) {
    BattleSide_SetChara((s32)arg0, 0x5F);
    func_00217CB8((s32)arg0);
    *(s32 *)(arg0 + 0x1454) += 1;
}
