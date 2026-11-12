#include "common.h"

void *BtlMember_GetActiveGauge(s32 arg0);

/* adds arg1 to the gauge at +0xC of the active member (when arg1 > 0), clamped to the value at +0x10 */
void func_00203810(s32 arg0, s32 arg1) {
    u8 *g = (u8 *)BtlMember_GetActiveGauge(arg0);
    if (arg1 > 0) {
        s32 max = *(s32 *)(g + 0x10);
        s32 v = *(s32 *)(g + 0xC) + arg1;
        *(s32 *)(g + 0xC) = v;
        if (max < v) {
            *(s32 *)(g + 0xC) = max;
        }
    }
}
