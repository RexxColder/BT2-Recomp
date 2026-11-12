#include "common.h"

void BtlOpp_GetDelta(s32 arg0, s32 arg1);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 func_00210D50(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_00217BD0(u8 *arg0) {
    s32 sp[4];
    f32 f20;

    if (!((*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0xE54)) & 3)) {
        if (func_00211310((s32)arg0, 4, 0x80) != 0) {
            if (func_00211310((s32)arg0, 4, 0x100) != 0) {
                return 1;
            }
            BtlOpp_GetDelta((s32)arg0, (s32)sp);
            f20 = *(f32 *)&sp[1];
            if (0.0f < f20) {
                if (f20 < func_00210D50((s32)arg0) * 0.5f) {
                    return 1;
                }
                return 0;
            }
            f20 = -f20;
            if (f20 < BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534)) * 0.5f) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 1;
}
