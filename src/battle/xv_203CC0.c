#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: BtlMember_GetActiveGauge(func_00211288(arg0)) (tail call), else 0 */
s32 func_00203CC0(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        return BtlMember_GetActiveGauge(func_00211288(arg0));
    }
    return 0;
}
