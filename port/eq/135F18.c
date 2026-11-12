#include "common.h"
#include "vu0_state.h"

/* 0x00135F18: arg0 = (rows 0..3 of arg1 * (v, 1)) with xyz divided by w (VU0 vmulax / vmadday / vmaddaz / vmaddw
 * with vf0.w = 1, vdiv, vmulq.xyz); w is kept. */
void func_00135F18(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 acc[4];
    f32 q;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = arg1[i];
        gVu0.vf[2][i] = arg1[4 + i];
        gVu0.vf[3][i] = arg1[8 + i];
        gVu0.vf[4][i] = arg1[12 + i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[1][i] * arg2[0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[2][i] * arg2[1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[3][i] * arg2[2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[6][i] = acc[i] + gVu0.vf[4][i] * gVu0.vf[0][3];
    }
    q = 1.0f / gVu0.vf[6][3];
    for (i = 0; i < 3; i++) {
        gVu0.vf[6][i] = gVu0.vf[6][i] * q;
    }
    for (i = 0; i < 4; i++) {
        arg0[i] = gVu0.vf[6][i];
    }
}
