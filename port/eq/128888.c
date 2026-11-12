#include "common.h"
#include "vu0_state.h"

/* 0x00128888 Mtx_Mul(dst, a, b): vf4..vf7 = a's rows, vf8..vf11 = b's rows; dst row r = ((a0 * b[r][0] + a1 * b[r][1])
 * + a2 * b[r][2]) + a3 * b[r][3], lane by lane (the four results also end up in vf8..vf11). */
void Mtx_Mul(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 acc[4];
    f32 b[4][4];
    s32 r;
    s32 i;

    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            gVu0.vf[4 + r][i] = arg1[r * 4 + i];
            b[r][i] = arg2[r * 4 + i];
            gVu0.vf[8 + r][i] = b[r][i];
        }
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            acc[i] = gVu0.vf[4][i] * b[r][0];
            acc[i] = acc[i] + gVu0.vf[5][i] * b[r][1];
            acc[i] = acc[i] + gVu0.vf[6][i] * b[r][2];
            gVu0.acc[i] = acc[i];
            gVu0.vf[8 + r][i] = acc[i] + gVu0.vf[7][i] * b[r][3];
        }
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            arg0[r * 4 + i] = gVu0.vf[8 + r][i];
        }
    }
}
