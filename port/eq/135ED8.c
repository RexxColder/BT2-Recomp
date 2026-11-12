#include "common.h"
#include "vu0_state.h"

/* 0x00135ED8: VU0 transform of a1[4] by the matrix in vf24..vf27 (gVu0) with vmulax/vmadday/vmaddaz/vmaddw, then
 * perspective divide by w (Q = 1 / w). vf5 = scaled result: a0 = { int(x*16), int(y*16), int(z), int(w) }.
 * vf6 = a2 with z = vf13.z, xyz scaled by Q, stored back to a2. VU state (vf4..vf6, ACC, Q) is written to gVu0. */
void func_00135ED8(s32 *arg0, f32 *arg1, f32 *arg2) {
    f32 v4[4];
    f32 v5[4];
    f32 v6[4];
    f32 acc[4];
    f32 q;
    s32 out[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        v4[i] = arg1[i];
        v6[i] = arg2[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[24][i] * v4[0];
        acc[i] = acc[i] + gVu0.vf[25][i] * v4[1];
        acc[i] = acc[i] + gVu0.vf[26][i] * v4[2];
        v5[i] = acc[i] + gVu0.vf[27][i] * v4[3];
    }
    v6[2] = gVu0.vf[13][2];
    q = 1.0f / v5[3];
    for (i = 0; i < 3; i++) {
        v5[i] = v5[i] * q;
        v6[i] = v6[i] * q;
    }
    out[0] = (s32)(v5[0] * 16.0f);
    out[1] = (s32)(v5[1] * 16.0f);
    out[2] = (s32)v5[2];
    out[3] = (s32)v5[3];

    for (i = 0; i < 4; i++) {
        arg0[i] = out[i];
        arg2[i] = v6[i];
        ((s32 *)gVu0.vf[4])[i] = out[i];
        gVu0.vf[5][i] = v5[i];
        gVu0.vf[6][i] = v6[i];
        gVu0.acc[i] = acc[i];
    }
    gVu0.q = q;
}
