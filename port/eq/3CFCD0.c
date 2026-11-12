#include "common.h"

/* 0x003CFCD0: out[0..7] (s32 at arg3) = 1; then for the 7 entries of the u16 list arg2 (w = *p, skipped when 0): rec =
 * arg0 + 48*w, k = *(rec - 8) (skipped when negative), t1 = arg1 + 44*k: out[j] += *(s32 *)(t1 + 8 + 4*j) for j = 0..7,
 * and acc |= the u64 at t1. Then out[j] = min(out[j], arg4) for j = 0..7 (signed). Returns acc. */
s64 func_003CFCD0(u8 *arg0, u8 *arg1, u16 *arg2, s32 *arg3, s32 arg4) {
    s64 acc;
    s32 j;
    s32 t4;
    u16 *p;

    acc = 0;
    for (j = 0; j < 8; j++) {
        arg3[j] = 1;
    }

    p = arg2;
    for (t4 = 6; t4 >= 0; t4--) {
        u16 w = *p;

        if (w != 0) {
            u8 *rec = arg0 + w * 48;
            s32 k = *(s32 *)(rec - 8);

            if (k >= 0) {
                u8 *t1 = arg1 + k * 44;

                for (j = 0; j < 8; j++) {
                    arg3[j] += *(s32 *)(t1 + 8 + 4 * j);
                }
                acc |= (s64)((u64)*(u32 *)t1 | ((u64)*(u32 *)(t1 + 4) << 32));
            }
        }
        p++;
    }

    for (j = 0; j < 8; j++) {
        if (arg4 < arg3[j]) {
            arg3[j] = arg4;
        }
    }

    return acc;
}
