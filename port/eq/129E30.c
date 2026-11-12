#include "common.h"
#include "vu0_state.h"

/* 0x00129E30(a0): squared length of the vector at a0 (xyz, vf15.x as the weight of z), returned in f0. */
f32 func_00129E30(u8 *arg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg0, 16);
    for (i = 0; i < 3; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] * gVu0.vf[4][i];
    }
    gVu0.acc[0] = gVu0.vf[4][0] + gVu0.vf[4][1];
    gVu0.vf[4][0] = gVu0.acc[0] + gVu0.vf[15][0] * gVu0.vf[4][2];
    return gVu0.vf[4][0];
}
