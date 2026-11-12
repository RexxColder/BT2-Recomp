#include "common.h"

/* 0x00273388(p, q): p holds f32 at +0xC (A), +0x10 (B), +0x18 (C); q holds f32 at +0, +4 (the origin) and three
 * pairs (u at +8 + 4k, w at +0x14 + 4k). With d1 = B - q0 and d2 = C - q1, t = u * d1 + w * d2 per k: t < -A
 * clears a3, and A < t false (t <= A or NaN) sets a2. Returns a2 when a3 is set, else 2. */
s32 func_00273388(u8 *arg0, u8 *arg1) {
    f32 a = *(f32 *)(arg0 + 0xC);
    f32 neg_a = -a;
    f32 d1 = *(f32 *)(arg0 + 0x10) - *(f32 *)(arg1 + 0);
    f32 d2 = *(f32 *)(arg0 + 0x18) - *(f32 *)(arg1 + 4);
    s32 a2 = 0;
    s32 a3 = 1;
    s32 k;

    for (k = 0; k < 3; k++) {
        f32 u = *(f32 *)(arg1 + 8 + 4 * k);
        f32 w = *(f32 *)(arg1 + 0x14 + 4 * k);
        f32 t = u * d1;
        t = t + w * d2;
        if (t < neg_a) {
            a3 = 0;
        } else if (!(a < t)) {
            a2 = 1;
        }
    }
    return (a3 != 0) ? a2 : 2;
}
