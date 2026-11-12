#include "common.h"
#include "vu0_state.h"

extern f32 sqrtf(f32 farg0);

/* 0x001EEDB8: arg0.xyz = normalize(arg1.xyz) * farg0, arg0.w = arg1.w (VU0 vmul.xyz / vadday / vmaddz with vf15.x,
 * vrsqrt, vmulq.xyz, vmulx.xyz by the scalar). */
void func_001EEDB8(f32 *arg0, f32 *arg1, f32 farg0) {
    f32 xx = arg1[0] * arg1[0];
    f32 yy = arg1[1] * arg1[1];
    f32 zz = arg1[2] * arg1[2];
    f32 dot = (xx + yy) + gVu0.vf[15][0] * zz;
    f32 q = 1.0f / sqrtf(dot);
    s32 i;

    for (i = 0; i < 3; i++) {
        arg0[i] = (arg1[i] * q) * farg0;
    }
    arg0[3] = arg1[3];
}
