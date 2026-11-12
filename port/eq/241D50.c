#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0);

s32 func_00241D50(u8 *arg0, s32 arg1) {
    u8 *gauge;
    u8 *tab;
    s32 off;
    s32 prod;

    off = (arg1 != 0) * 4;
    gauge = BtlMember_GetActiveGauge((s32)arg0);
    tab = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0x984);
    prod = (s32)((u32)*(s32 *)(gauge + 0x4) * (u32)*(s32 *)(tab + off + 0x38));
    return prod / 100;
}
