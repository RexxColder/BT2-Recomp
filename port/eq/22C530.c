#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0022C530(u8 *arg0) {
    BattleSide_SetChara((s32)arg0, 0x3A);
    func_002113C0((s32)arg0, 0, 2, 1);
    if (*(s32 *)(arg0 + 0xB84) > 0) {
        *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 2;
    }
}
