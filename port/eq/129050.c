#include "common.h"
#include "vu0_state.h"

/* 0x00129050 (BT3 Vu0Cur_MulMtxRev, fuzzy): each row k = 16..19 of gVu0 (a row vector v) becomes v * M, where M is
 * the 4x4 float matrix at a0 (rows vf4..vf7 in the asm): out[i] = M0[i]*v0 + M1[i]*v1 + M2[i]*v2 + M3[i]*v3. */
void func_00129050(f32 *arg0) {
    f32 m[4][4];
    f32 out[4][4];
    f32 acc[4];
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m[i][j] = arg0[i * 4 + j];
        }
    }
    for (k = 0; k < 4; k++) {
        for (i = 0; i < 4; i++) {
            acc[i] = m[0][i] * gVu0.vf[16 + k][0];
            acc[i] = acc[i] + m[1][i] * gVu0.vf[16 + k][1];
            acc[i] = acc[i] + m[2][i] * gVu0.vf[16 + k][2];
            out[k][i] = acc[i] + m[3][i] * gVu0.vf[16 + k][3];
        }
    }
    for (k = 0; k < 4; k++) {
        for (i = 0; i < 4; i++) {
            gVu0.vf[16 + k][i] = out[k][i];
        }
    }
}
