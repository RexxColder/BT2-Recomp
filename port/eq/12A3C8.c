#include "common.h"

/* 0x0012A3C8 Vec4_AddClamp: out = min(max(a + b, lo), hi) on four components (VU0 vadd / vmaxx / vminix). */
void Vec4_AddClamp(f32 *arg0, f32 *arg1, f32 *arg2, f32 farg0, f32 farg1) {
    s32 i;

    for (i = 0; i < 4; i++) {
        f32 v = arg1[i] + arg2[i];

        if (v < farg0) {
            v = farg0;
        }
        if (v > farg1) {
            v = farg1;
        }
        arg0[i] = v;
    }
}
