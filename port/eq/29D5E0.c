#include "common.h"
#include "vu0_state.h"

/* 0x0029D5E0(a, b, c): vf1..vf4 = copies of vf28..vf31; the blocks (a,0,0,0), (0,b,0,0), (0,0,c,0), (0,0,0,1) are
 * loaded into vf5..vf8, and vf28..vf31 = vf1..vf4 times vf5..vf8 (columns, lanes summed in VU order). */
void func_0029D5E0(f32 arg0, f32 arg1, f32 arg2) {
    f32 m[4][4];
    f32 b[4][4] = {
        { arg0, 0.0f, 0.0f, 0.0f },
        { 0.0f, arg1, 0.0f, 0.0f },
        { 0.0f, 0.0f, arg2, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
    };
    f32 out[4][4];
    s32 j;
    s32 k;

    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            m[j][k] = gVu0.vf[28 + j][k];
        }
    }
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            f32 acc = m[0][k] * b[j][0];
            acc = acc + m[1][k] * b[j][1];
            acc = acc + m[2][k] * b[j][2];
            acc = acc + m[3][k] * b[j][3];
            out[j][k] = acc;
        }
    }
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            gVu0.vf[1 + j][k] = m[j][k];
            gVu0.vf[5 + j][k] = b[j][k];
            gVu0.vf[28 + j][k] = out[j][k];
        }
    }
}
