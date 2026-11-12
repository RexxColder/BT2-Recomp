#include "common.h"
#include "vu0_state.h"

f32 cosf(f32 arg0);
f32 sinf(f32 arg0);

/* 0x0029C8E0(angle): c = cos(angle), s = sin(angle); vf1 = (c, -s, 0, 0), vf2 = (s, c, 0, 0); the rotated pair
 * vf4 = vf28 * c + vf29 * -s (+ vf30 * 0 + vf31 * 0) and vf3 = vf28 * s + vf29 * c (+ the same zero terms),
 * then vf28 = vf4 and vf29 = vf3. */
void func_0029C8E0(f32 arg0) {
    f32 c = cosf(arg0);
    f32 s = sinf(arg0);
    f32 v1[4];
    f32 v2[4];
    f32 v3[4];
    f32 v4[4];
    s32 k;

    v1[0] = c;
    v1[1] = 0.0f - s;
    v1[2] = 0.0f;
    v1[3] = 0.0f;
    v2[0] = s;
    v2[1] = c;
    v2[2] = 0.0f;
    v2[3] = 0.0f;
    for (k = 0; k < 4; k++) {
        f32 acc = gVu0.vf[28][k] * v1[0];
        acc = acc + gVu0.vf[29][k] * v1[1];
        acc = acc + gVu0.vf[30][k] * v1[2];
        acc = acc + gVu0.vf[31][k] * v1[3];
        v4[k] = acc;
    }
    for (k = 0; k < 4; k++) {
        f32 acc = gVu0.vf[28][k] * v2[0];
        acc = acc + gVu0.vf[29][k] * v2[1];
        acc = acc + gVu0.vf[30][k] * v2[2];
        acc = acc + gVu0.vf[31][k] * v2[3];
        v3[k] = acc;
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
