#include "common.h"
#include "vu0_state.h"

/* Vec3_ScaleAdd(out a0, a a1, b a2, f12 s): out.xyz = a * s + b, out.w = b.w. */
void Vec3_ScaleAdd(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    gVu0.vf[6][0] = farg0;
    memcpy(gVu0.vf[5], arg2, 16);
    for (i = 0; i < 3; i++) {
        gVu0.acc[i] = gVu0.vf[4][i] * gVu0.vf[6][0];
    }
    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.acc[i] + gVu0.vf[5][i] * gVu0.vf[0][3];
    }
    memcpy(arg0, gVu0.vf[5], 16);
}
