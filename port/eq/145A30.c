#include "common.h"
#include "vu0_state.h"

/* 0x00145A30: a0 = a1 - a2 on xyz, w of a1 kept (VU0 vsub.xyz through vf1 / vf2). */
void func_00145A30(f32 *arg0, f32 *arg1, f32 *arg2) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = arg1[i];
        gVu0.vf[2][i] = arg2[i];
    }
    for (i = 0; i < 3; i++) {
        gVu0.vf[1][i] = gVu0.vf[1][i] - gVu0.vf[2][i];
    }
    for (i = 0; i < 4; i++) {
        arg0[i] = gVu0.vf[1][i];
    }
}
