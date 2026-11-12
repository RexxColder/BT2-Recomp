#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023F410(s32 arg0);
u8 *BtlMember_GetActiveGauge(s32 arg0, s32 arg1);

s32 BattleSide_GetStartChara(s32 arg0) {
    s32 a1v;
    u8 *g;

    if (func_00211310(arg0, 0, 2) != 0) {
        a1v = 0;
        if ((func_0023F410(arg0) & 0x1000) != 0) {
            a1v = 0x1A4;
            if (func_00211310(arg0, 0, 0x100) == 0) {
                return a1v;
            }
        }
        g = BtlMember_GetActiveGauge(arg0, a1v);
        return (*(u8 *)(g + 0x29) == 0) ? 0x32 : 0x33;
    }
    g = BtlMember_GetActiveGauge(arg0, 0);
    return *(u8 *)(g + 0x29) != 0;
}
