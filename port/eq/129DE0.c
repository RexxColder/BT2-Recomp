#include "common.h"

/* 0x00129DE0 Vec3_Lerp: dst.xyz = a*t + b*(1 - t) (VU0 vmulax.xyz / vmaddw.xyz). dst.w is the upper word of the t
 * register in the original: GUESS, written as 0. */
void Vec3_Lerp(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    f32 s = 1.0f - arg3;
    s32 i;

    for (i = 0; i < 3; i++) {
        f32 p = arg1[i] * arg3;
        f32 q = arg2[i] * s;

        arg0[i] = p + q;
    }
    arg0[3] = 0.0f;
}
