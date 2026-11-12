#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020B2B8(s32 arg0) {
    if (D_00387930 != 0 && (u32)arg0 < 2U) {
        u8 *gauge = BtlMember_GetActiveGauge(func_00211288(arg0));

        if (*(s32 *)(gauge + 4) / 2 >= *(s32 *)gauge) {
            return *(u8 *)(gauge + 0x28) != 0;
        }
        return 0;
    }
    return 0;
}
