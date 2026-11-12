#include "m2c_macros.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_00212DD8(s32 arg0, s32 arg1);

void func_00225E10(void *arg0) {
    BattleSide_SetChara((s32)arg0, 0x19E);
    func_00212DD8((s32)arg0, 0x23);
    *(s32 *)((u8 *)arg0 + 0x1458) = *(s32 *)((u8 *)arg0 + 0x1458) + 1;
}
