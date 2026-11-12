#include "common.h"

/* 0x00129D68 Vec4_Clamp: out = min(max(in, lo), hi) on four components (VU0 vmaxx / vminix). */
void Vec4_Clamp(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 4; i++) {
        f32 v = arg1[i];

        if (v < arg2) {
            v = arg2;
        }
        if (v > arg3) {
            v = arg3;
        }
        arg0[i] = v;
    }
}
