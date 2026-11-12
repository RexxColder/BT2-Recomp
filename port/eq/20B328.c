#include "common.h"

extern u8 *D_00387930;
s32 func_00211288(s32 arg0, s32 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);

s32 func_0020B328(u32 arg0, s32 arg1) {
    s32 x;
    s32 g;

    if (D_00387930 == 0) {
        return 0;
    }
    if (arg0 >= 2) {
        return 0;
    }
    x = func_00211288((s32)arg0, arg1);
    g = BtlMember_GetActiveGauge(x);
    return *(u8 *)(g + 0x2C) != 0;
}
