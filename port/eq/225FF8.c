#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00217490(s32 arg0);
s32 func_0023F410(s32 arg0);

void func_00225FF8(u8 *arg0) {
    if (func_00217490((s32)arg0) != 0x87) {
        *(s32 *)(arg0 + 0xA18) = 0;
        func_00211418((s32)arg0, 0x8000);
    }
    if (*(s32 *)(arg0 + 0xA18) != 0) {
        BattleSide_SetChara((s32)arg0, 0x7E);
        if ((*(u8 *)(BtlMember_GetActiveGauge((s32)arg0) + 0x2C) == 0) && !(func_0023F410((s32)arg0) & 0x100)) {
            *(s32 *)(arg0 + 0xA18) = 0;
        }
    } else {
        BattleSide_SetChara((s32)arg0, 0x7D);
        *(s32 *)(arg0 + 0xA18) = 1;
    }
    *(s32 *)(arg0 + 0xA14) = 0x1E;
    *(s32 *)(arg0 + 0xA10) = *(s32 *)(arg0 + 0xA10) + 1;
}
