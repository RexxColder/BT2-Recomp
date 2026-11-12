#include "common.h"

/* 0x00129920: three rows of 4 words (VU0): dst[r][i] = a1[r][i] * t + a2[r][i] * (1 - t), t = f12
 * (vsubx.w gives 1 - t in vf3.w, vmulax / vmaddw do the lerp). */
void func_00129920(f32 *arg0, f32 *arg1, f32 *arg2, f32 farg0) {
    f32 u = 1.0f - farg0;
    s32 r;
    s32 i;

    for (r = 0; r < 3; r++) {
        for (i = 0; i < 4; i++) {
            arg0[r * 4 + i] = arg1[r * 4 + i] * farg0 + arg2[r * 4 + i] * u;
        }
    }
}
