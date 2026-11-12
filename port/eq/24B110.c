#include "common.h"

/* 0x0024B110: sets the 8 words at arg3 to 1. For each of 7 entries (4 bytes apart) of arg2: idx = word at the
 * entry; if idx != 0, v = *(s32 *)(arg0 + 48*idx - 8); if v >= 0, then for i in 0..7: arg3[i] += *(s32 *)(arg1 +
 * 44*v + 8 + 4*i), and the accumulator |= the 64-bit word at arg1 + 44*v. Finally arg3[i] = min(arg3[i], arg4)
 * (signed) for i in 0..7. Returns the accumulator. */
u64 func_0024B110(u8 *arg0, u8 *arg1, u8 *arg2, s32 *arg3, s32 arg4) {
    u64 acc = 0;
    s32 n;
    s32 i;
    u8 *entry = arg2;

    for (i = 0; i < 8; i++) {
        arg3[i] = 1;
    }
    for (n = 6; n >= 0; n--, entry += 4) {
        s32 idx = *(s32 *)entry;
        s32 v;
        u8 *t1;

        if (idx == 0) {
            continue;
        }
        v = *(s32 *)(arg0 + (s32)idx * 48 - 8);
        if (v < 0) {
            continue;
        }
        t1 = arg1 + v * 44;
        for (i = 0; i < 8; i++) {
            arg3[i] += *(s32 *)(t1 + 8 + 4 * i);
            acc |= (u64)*(u32 *)t1;
            acc |= (u64)*(u32 *)(t1 + 4) << 32;
        }
    }
    for (i = 0; i < 8; i++) {
        if (arg4 < arg3[i]) {
            arg3[i] = arg4;
        }
    }
    return acc;
}
