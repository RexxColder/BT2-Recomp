#include "common.h"
#include "vu0_state.h"

/* 0x0028DB98(a0): f0 = x*x + y*y + z*z of the vector at a0 (vmul.xyz, vaddy.x, vaddz.x). */
f32 func_0028DB98(u8 *arg0) {
    s32 i;

    memcpy(gVu0.vf[5], arg0, 16);
    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.vf[5][i] * gVu0.vf[5][i];
    }
    gVu0.vf[5][0] = gVu0.vf[5][0] + gVu0.vf[5][1];
    gVu0.vf[5][0] = gVu0.vf[5][0] + gVu0.vf[5][2];
    return gVu0.vf[5][0];
}
