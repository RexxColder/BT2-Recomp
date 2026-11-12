#include "common.h"
#include "vu0_state.h"

/* Vec3_Cross(out a0, a a1, b a2): out.xyz = a x b (the vopmula / vopmsub pair), out.w = 0 (vsub.w). */
void Vec3_Cross(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ax;
    f32 ay;
    f32 az;
    f32 bx;
    f32 by;
    f32 bz;

    memcpy(gVu0.vf[4], arg1, 16);
    memcpy(gVu0.vf[5], arg2, 16);
    ax = gVu0.vf[4][0];
    ay = gVu0.vf[4][1];
    az = gVu0.vf[4][2];
    bx = gVu0.vf[5][0];
    by = gVu0.vf[5][1];
    bz = gVu0.vf[5][2];
    gVu0.acc[0] = ay * bz;
    gVu0.acc[1] = az * bx;
    gVu0.acc[2] = ax * by;
    gVu0.vf[5][0] = ay * bz - az * by;
    gVu0.vf[5][1] = az * bx - ax * bz;
    gVu0.vf[5][2] = ax * by - ay * bx;
    gVu0.vf[5][3] = gVu0.vf[5][3] - gVu0.vf[5][3];
    memcpy(arg0, gVu0.vf[5], 16);
}
