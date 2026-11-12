#include "common.h"
#include "vu0_state.h"

/* 0x00128970 Mtx_InverseRT(dst, src). src rows A, B, C (words 0..11) and row T = src row 3. dst rows 0..2 are
 * (A0,B0,C0,0), (A1,B1,C1,0), (A2,B2,C2,0) (the 3x3 transposed); dst row 3 = (-(A0 Tx + A1 Ty + A2 Tz),
 * -(B0 Tx + B1 Ty + B2 Tz), -(C0 Tx + C1 Ty + C2 Tz), T.w). The VU0 work is on vf4..vf8 and ACC. */
void Mtx_InverseRT(f32 *dst, f32 *src) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = src[12 + i];   /* lqc2 vf4, 0x30(a1) */
        gVu0.vf[5][i] = src[12 + i];   /* vmove.xyzw vf5, vf4 */
    }
    gVu0.vf[4][0] = gVu0.vf[0][0];     /* vmove.xyz vf4, vf0 */
    gVu0.vf[4][1] = gVu0.vf[0][1];
    gVu0.vf[4][2] = gVu0.vf[0][2];

    gVu0.vf[6][0] = src[0];  gVu0.vf[6][1] = src[4];  gVu0.vf[6][2] = src[8];   gVu0.vf[6][3] = 0.0f;
    gVu0.vf[7][0] = src[1];  gVu0.vf[7][1] = src[5];  gVu0.vf[7][2] = src[9];   gVu0.vf[7][3] = 0.0f;
    gVu0.vf[8][0] = src[2];  gVu0.vf[8][1] = src[6];  gVu0.vf[8][2] = src[10];  gVu0.vf[8][3] = 0.0f;

    /* vmulax.xyz ACC, vf6, Tx; vmadday.xyz ACC, vf7, Ty; vmaddz.xyz vf4, vf8, Tz; vsub.xyz vf4, vf0, vf4 */
    for (i = 0; i < 3; i++) {
        gVu0.acc[i] = gVu0.vf[6][i] * gVu0.vf[5][0] + gVu0.vf[7][i] * gVu0.vf[5][1];
        gVu0.vf[4][i] = 0.0f - (gVu0.acc[i] + gVu0.vf[8][i] * gVu0.vf[5][2]);
    }

    for (i = 0; i < 4; i++) {
        dst[0 + i] = gVu0.vf[6][i];
        dst[4 + i] = gVu0.vf[7][i];
        dst[8 + i] = gVu0.vf[8][i];
        dst[12 + i] = gVu0.vf[4][i];
    }
}
