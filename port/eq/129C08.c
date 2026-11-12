#include "common.h"
#include "vu0_state.h"

/* Vec3_Div(out a0, a a1, f12 d): Q = 1 / d; out.xyz = a * Q, out.w = a.w. */
void Vec3_Div(u8 *arg0, u8 *arg1, f32 farg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    gVu0.vf[5][0] = farg0;
    gVu0.q = gVu0.vf[0][3] / gVu0.vf[5][0];
    for (i = 0; i < 3; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] * gVu0.q;
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
