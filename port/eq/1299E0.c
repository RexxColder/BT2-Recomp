#include "common.h"
#include "vu0_state.h"

/* 0x001299E0(out_int, out_f, m, v, count): vf4..vf7 = m's rows. For each of count vectors P (P0 = v, step 0x30 bytes):
 * vf8 = P[0..3], vf3 = P[4..7] (its z lane is replaced by vf13.z), vf9 = m * vf8 (ACC order as in the matrix
 * products), Q = 1 / vf9.w, vf9.xyz *= Q, vf2 = vf3.xyz * Q (vf2.w keeps its value). out_int gets
 * (x*16, y*16 truncated, z, w truncated) from vf9; out_f gets vf2. Both outputs advance 16 bytes per vector. */
void func_001299E0(s32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    f32 *p = arg3;
    f32 acc[4];
    f32 q;
    s32 n = arg4;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = arg2[0 + i];
        gVu0.vf[5][i] = arg2[4 + i];
        gVu0.vf[6][i] = arg2[8 + i];
        gVu0.vf[7][i] = arg2[12 + i];
        gVu0.vf[8][i] = p[i];
        gVu0.vf[3][i] = p[4 + i];
    }

    do {
        for (i = 0; i < 4; i++) {
            acc[i] = gVu0.vf[4][i] * gVu0.vf[8][0];
            acc[i] = acc[i] + gVu0.vf[5][i] * gVu0.vf[8][1];
            acc[i] = acc[i] + gVu0.vf[6][i] * gVu0.vf[8][2];
            gVu0.acc[i] = acc[i];
            gVu0.vf[9][i] = acc[i] + gVu0.vf[7][i] * gVu0.vf[8][3];
        }
        q = 1.0f / gVu0.vf[9][3];
        gVu0.q = q;
        gVu0.vf[3][2] = gVu0.vf[13][2];
        for (i = 0; i < 3; i++) {
            gVu0.vf[9][i] = gVu0.vf[9][i] * q;
            gVu0.vf[2][i] = gVu0.vf[3][i] * q;
        }
        arg0[0] = (s32)(gVu0.vf[9][0] * 16.0f);
        arg0[1] = (s32)(gVu0.vf[9][1] * 16.0f);
        arg0[2] = (s32)gVu0.vf[9][2];
        arg0[3] = (s32)gVu0.vf[9][3];
        for (i = 0; i < 4; i++) {
            arg1[i] = gVu0.vf[2][i];
        }

        p += 12;
        for (i = 0; i < 4; i++) {
            gVu0.vf[8][i] = p[i];
            gVu0.vf[3][i] = p[4 + i];
        }
        arg0 += 4;
        arg1 += 4;
        n -= 1;
    } while (n != 0);
}
