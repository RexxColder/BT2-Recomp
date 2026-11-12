#include "common.h"
#include "vu0_state.h"

/* 0x00135EA0: out = (matrix vf24..vf27 * (v, 1)) with the perspective divide on xyz by w (VU0 vdiv / vmulq / vftoi4
 * on xy, vftoi0 on zw). The lanes of vf6 are scaled too. Truncating conversions. */
void func_00135EA0(s32 *arg0, f32 *arg1) {
    f32 acc[4];
    f32 q;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = arg1[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[24][i] * gVu0.vf[4][0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[25][i] * gVu0.vf[4][1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[26][i] * gVu0.vf[4][2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[5][i] = acc[i] + gVu0.vf[27][i] * gVu0.vf[4][3];
    }
    q = 1.0f / gVu0.vf[5][3];
    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.vf[5][i] * q;
        gVu0.vf[6][i] = gVu0.vf[6][i] * q;
    }
    arg0[0] = (s32)(gVu0.vf[5][0] * 16.0f);
    arg0[1] = (s32)(gVu0.vf[5][1] * 16.0f);
    arg0[2] = (s32)gVu0.vf[5][2];
    arg0[3] = (s32)gVu0.vf[5][3];
}
