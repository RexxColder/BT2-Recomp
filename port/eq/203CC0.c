#include "common.h"

/* 0x00203CC0: if (!D_00387930) return 0; if (!((u32)a0 < 2)) return 0; return BtlMember_GetActiveGauge(func_00211288(a0)). */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);

s32 func_00203CC0(s32 a0) {
    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    return BtlMember_GetActiveGauge(func_00211288(a0));
}
