#include "common.h"
#include "vu0_state.h"

/* 0x00129158 Vu0Cur_InverseRT(): the current matrix (rows vf16..vf19 = A, B, C, T) is replaced in place by its
 * rotation-translation inverse: rows 0..2 = (A0,B0,C0,0), (A1,B1,C1,0), (A2,B2,C2,0); row 3 = (-(A0 Tx + A1 Ty +
 * A2 Tz), -(B0 Tx + B1 Ty + B2 Tz), -(C0 Tx + C1 Ty + C2 Tz), T.w). Same arithmetic as Mtx_InverseRT. */
void Vu0Cur_InverseRT(void) {
    f32 col[3][4];
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = gVu0.vf[19][i];   /* vmove.xyzw vf4, vf19 */
    }
    gVu0.vf[4][0] = gVu0.vf[0][0];        /* vmove.xyz vf4, vf0 */
    gVu0.vf[4][1] = gVu0.vf[0][1];
    gVu0.vf[4][2] = gVu0.vf[0][2];

    for (i = 0; i < 3; i++) {
        col[0][i] = gVu0.vf[16 + i][0];   /* vf6 = (A0, B0, C0, 0) */
        col[1][i] = gVu0.vf[16 + i][1];   /* vf7 = (A1, B1, C1, 0) */
        col[2][i] = gVu0.vf[16 + i][2];   /* vf8 = (A2, B2, C2, 0) */
    }
    col[0][3] = 0.0f;
    col[1][3] = 0.0f;
    col[2][3] = 0.0f;
    for (i = 0; i < 4; i++) {
        gVu0.vf[6][i] = col[0][i];
        gVu0.vf[7][i] = col[1][i];
        gVu0.vf[8][i] = col[2][i];
    }

    for (i = 0; i < 3; i++) {
        gVu0.acc[i] = gVu0.vf[6][i] * gVu0.vf[19][0] + gVu0.vf[7][i] * gVu0.vf[19][1];
        gVu0.vf[4][i] = 0.0f - (gVu0.acc[i] + gVu0.vf[8][i] * gVu0.vf[19][2]);
    }

    for (i = 0; i < 4; i++) {
        gVu0.vf[16][i] = gVu0.vf[6][i];
        gVu0.vf[17][i] = gVu0.vf[7][i];
        gVu0.vf[18][i] = gVu0.vf[8][i];
        gVu0.vf[19][i] = gVu0.vf[4][i];
    }
}
