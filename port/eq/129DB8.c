#include "common.h"

/* 0x00129DB8 Vec4_Lerp: dst = a*t + b*(1 - t) on four components (VU0 vmulax / vmaddw; 1 - t from vsubx.w). */
void Vec4_Lerp(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    f32 s = 1.0f - arg3;
    s32 i;

    for (i = 0; i < 4; i++) {
        f32 p = arg1[i] * arg3;
        f32 q = arg2[i] * s;

        arg0[i] = p + q;
    }
}
