#include "common.h"

/* 0x00203810: gauge = BtlMember_GetActiveGauge(a0); if (a1 > 0) { gauge[3] += a1; clamp to gauge[4] }.
 * Returns the gauge pointer, or the new sum when a1 > 0 (stale v0). */
s32 BtlMember_GetActiveGauge(s32 arg0);

s32 func_00203810(s32 a0, s32 a1) {
    u8 *gauge;
    s32 max;
    s32 sum;

    gauge = (u8 *)BtlMember_GetActiveGauge(a0);
    if (a1 > 0) {
        max = *(s32 *)(gauge + 0x10);
        sum = *(s32 *)(gauge + 0xC) + a1;
        *(s32 *)(gauge + 0xC) = sum;
        if (max < sum) {
            *(s32 *)(gauge + 0xC) = max;
        }
        return sum;
    }
    return (s32)gauge;
}
