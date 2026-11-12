#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
u8 *BtlMember_GetActiveGauge(u8 *arg0);

/* 0x0023B0C8: per-frame countdowns on obj: +0xAE0/+0xAE8/+0xADC/+0xAF0 decrement clamped at 0 (AE0/AE8 also zero their
 * partner +0xAE4/+0xAEC); +0xAD8 = max(v-1,0), set to 1 when byte +0xAF4 or +0xAF5 is set; AF0 cleared when the active gauge
 * has c <= 0, when func_00211310(obj,1,1) or func_00211310(obj,8,4) returns nonzero. */
void func_0023B0C8(u8 *arg0) {
    s32 t;
    u8 *g;

    t = *(s32 *)(arg0 + 0xAE0) - 1;
    *(s32 *)(arg0 + 0xAE0) = t;
    if (t < 0) {
        *(s32 *)(arg0 + 0xAE0) = 0;
        *(s32 *)(arg0 + 0xAE4) = 0;
    }
    t = *(s32 *)(arg0 + 0xAE8) - 1;
    *(s32 *)(arg0 + 0xAE8) = t;
    if (t < 0) {
        *(s32 *)(arg0 + 0xAE8) = 0;
        *(s32 *)(arg0 + 0xAEC) = 0;
    }
    t = *(s32 *)(arg0 + 0xAD8) - 1;
    if (t < 0) {
        t = 0;
    }
    *(s32 *)(arg0 + 0xAD8) = t;
    if (arg0[0xAF4] != 0) {
        *(s32 *)(arg0 + 0xAD8) = 1;
    }
    if (arg0[0xAF5] != 0) {
        *(s32 *)(arg0 + 0xAD8) = 1;
    }
    t = *(s32 *)(arg0 + 0xADC) - 1;
    if (t < 0) {
        t = 0;
    }
    *(s32 *)(arg0 + 0xADC) = t;
    t = *(s32 *)(arg0 + 0xAF0) - 1;
    if (t < 0) {
        t = 0;
    }
    *(s32 *)(arg0 + 0xAF0) = t;
    g = BtlMember_GetActiveGauge(arg0);
    if (*(s32 *)(g + 0xC) <= 0) {
        *(s32 *)(arg0 + 0xAF0) = 0;
    }
    if (func_00211310(arg0, 1, 1) != 0) {
        *(s32 *)(arg0 + 0xAF0) = 0;
    }
    if (func_00211310(arg0, 8, 4) != 0) {
        *(s32 *)(arg0 + 0xAF0) = 0;
    }
}
