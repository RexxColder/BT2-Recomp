#include "common.h"
#include "vu0_state.h"

/* 0x0029D8B8(a, b): vf1..vf4 = a's rows, vf5..vf8 = b's rows; out row i (vf24 + i) = ((a0 * b[i][0] + a1 * b[i][1])
 * + a2 * b[i][2]) + a3 * b[i][3], lane by lane. */
void func_0029D8B8(f32 *arg0, f32 *arg1) {
    f32 a[4][4];
    s32 r;
    s32 i;

    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            a[r][i] = arg0[r * 4 + i];
            gVu0.vf[1 + r][i] = a[r][i];
            gVu0.vf[5 + r][i] = arg1[r * 4 + i];
        }
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            gVu0.acc[i] = a[0][i] * arg1[r * 4 + 0];
            gVu0.acc[i] = gVu0.acc[i] + a[1][i] * arg1[r * 4 + 1];
            gVu0.acc[i] = gVu0.acc[i] + a[2][i] * arg1[r * 4 + 2];
            gVu0.vf[24 + r][i] = gVu0.acc[i] + a[3][i] * arg1[r * 4 + 3];
        }
    }
}
