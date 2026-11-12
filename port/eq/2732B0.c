#include "common.h"

s32 func_002732B0(u8 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    s32 t1;
    s32 t2;
    s32 t4;
    s32 t5;
    s32 a2;
    s32 a3;
    s32 bit;
    f32 xs;
    f32 ys;
    f32 p;
    f32 q;
    f32 sum;
    u8 *v1;
    u8 *a1;

    t4 = 0;
    t5 = -1;
    for (t2 = 0; t2 < 2; t2++) {
        for (t1 = 0; t1 < 2; t1++) {
            xs = (t1 != 0) ? (farg0 + farg2) : (farg0 - farg2);
            ys = (t2 != 0) ? (farg1 + farg2) : (farg1 - farg2);
            a2 = 0;
            bit = 1;
            v1 = arg0 + 8;
            a1 = arg0 + 4 + 0x10;
            for (a3 = 0; a3 < 3; a3++) {
                p = *(f32 *)v1;
                q = *(f32 *)a1;
                v1 += 4;
                sum = p * (xs - *(f32 *)arg0) + q * (ys - *(f32 *)(arg0 + 4));
                a1 += 4;
                if (sum < 0.0f) {
                    a2 |= bit;
                }
                bit *= 2;
            }
            t5 &= a2;
            t4 |= a2;
        }
    }
    if (t4 == 0) {
        return 0;
    }
    return (t5 == 0) ? 1 : 2;
}
