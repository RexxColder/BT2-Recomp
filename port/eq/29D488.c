#include "common.h"
#include "vu0_state.h"

f32 cosf(f32 arg0);
f32 sinf(f32 arg0);

/* 0x0029D488(v, angle): vf31 = M * v with M = (vf28..vf31 as columns); then rotate the pair vf28/vf29 by
 * angle: vf4 = c*vf28 - s*vf29 (+ 0 * vf30 + 0 * vf31), vf3 = s*vf28 + c*vf29, vf28 = vf4, vf29 = vf3.
 * c and s come from the stack copy the asm builds: (c, -s, 0, 0) and (s, c, 0, 0). */
void func_0029D488(void *arg0, f32 arg1) {
    f32 *in = (f32 *)arg0;
    f32 c;
    f32 s;
    f32 v1[4];
    f32 v2[4];
    f32 v3[4];
    f32 v4[4];
    f32 acc;
    s32 k;

    for (k = 0; k < 4; k++) {
        gVu0.vf[1][k] = in[k];
    }
    for (k = 0; k < 4; k++) {
        acc = gVu0.vf[28][k] * gVu0.vf[1][0];
        acc = acc + gVu0.vf[29][k] * gVu0.vf[1][1];
        acc = acc + gVu0.vf[30][k] * gVu0.vf[1][2];
        gVu0.vf[2][k] = acc + gVu0.vf[31][k] * gVu0.vf[1][3];
    }
    for (k = 0; k < 4; k++) {
        gVu0.vf[31][k] = gVu0.vf[2][k];
    }
    /* vf1 = (0,0,0,1), vf2 = (0,0,1,0), vf3 = (0,1,0,0), vf4 = (1,0,0,0) (the vmr32 chain) */
    c = cosf(arg1);
    s = sinf(arg1);
    v1[0] = c;
    v1[1] = -s;
    v1[2] = 0.0f;
    v1[3] = 0.0f;
    v2[0] = s;
    v2[1] = c;
    v2[2] = 0.0f;
    v2[3] = 0.0f;
    for (k = 0; k < 4; k++) {
        acc = gVu0.vf[28][k] * v1[0];
        acc = acc + gVu0.vf[29][k] * v1[1];
        acc = acc + gVu0.vf[30][k] * v1[2];
        v4[k] = acc + gVu0.vf[31][k] * v1[3];
    }
    for (k = 0; k < 4; k++) {
        acc = gVu0.vf[28][k] * v2[0];
        acc = acc + gVu0.vf[29][k] * v2[1];
        acc = acc + gVu0.vf[30][k] * v2[2];
        v3[k] = acc + gVu0.vf[31][k] * v2[3];
    }
    for (k = 0; k < 4; k++) {
        gVu0.vf[1][k] = v1[k];
        gVu0.vf[2][k] = v2[k];
        gVu0.vf[3][k] = v3[k];
        gVu0.vf[4][k] = v4[k];
        gVu0.vf[28][k] = v4[k];
        gVu0.vf[29][k] = v3[k];
    }
}
