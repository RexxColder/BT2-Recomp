#include "common.h"
#include "vu0_state.h"

f32 cosf(f32 x);
f32 sinf(f32 x);

/* VU0 macro code: builds a rotation basis from three angles (ang[0] -> block 1, ang[2] -> block 2,
 * ang[1] -> block 3) in vf28..vf30 and leaves vin * basis in vf31.xyz (vf31.w stays 1). */
void func_0029D6E8(f32 *vin, f32 *ang) {
    f32 c1, s1, c2, s2, c3, s3;
    f32 acc[4];
    f32 (*vf)[4] = gVu0.vf;
    s32 i;

    /* identity basis: vf28 = (1,0,0,0), vf29 = (0,1,0,0), vf30 = (0,0,1,0), vf31 = (0,0,0,1) */
    for (i = 0; i < 4; i++) {
        vf[28][i] = (i == 0) ? 1.0f : 0.0f;
        vf[29][i] = (i == 1) ? 1.0f : 0.0f;
        vf[30][i] = (i == 2) ? 1.0f : 0.0f;
        vf[31][i] = (i == 3) ? 1.0f : 0.0f;
    }

    /* block 1: angle ang[0] */
    c1 = cosf(ang[0]);
    s1 = sinf(ang[0]);
    vf[1][0] = 0.0f;
    vf[1][1] = c1;
    vf[1][2] = -s1;
    vf[1][3] = 0.0f;
    vf[2][0] = 0.0f;
    vf[2][1] = s1;
    vf[2][2] = c1;
    vf[2][3] = 0.0f;
    for (i = 0; i < 4; i++) {
        vf[3][i] = vf[1][i];
        vf[4][i] = vf[2][i];
    }
    for (i = 0; i < 4; i++) {
        vf[29][i] = vf[3][i];
        vf[30][i] = vf[4][i];
    }

    /* block 2: angle ang[2] */
    c2 = cosf(ang[2]);
    s2 = sinf(ang[2]);
    vf[1][0] = c2;
    vf[1][1] = -s2;
    vf[1][2] = 0.0f;
    vf[1][3] = 0.0f;
    vf[2][0] = s2;
    vf[2][1] = c2;
    vf[2][2] = 0.0f;
    vf[2][3] = 0.0f;
    for (i = 0; i < 4; i++) {
        vf[4][i] = vf[28][i] * vf[1][0] + vf[29][i] * vf[1][1] + vf[30][i] * vf[1][2] + vf[31][i] * vf[1][3];
        vf[3][i] = vf[28][i] * vf[2][0] + vf[29][i] * vf[2][1] + vf[30][i] * vf[2][2] + vf[31][i] * vf[2][3];
    }
    for (i = 0; i < 4; i++) {
        vf[28][i] = vf[4][i];
        vf[29][i] = vf[3][i];
    }

    /* block 3: angle ang[1] */
    c3 = cosf(ang[1]);
    s3 = sinf(ang[1]);
    vf[1][0] = c3;
    vf[1][1] = 0.0f;
    vf[1][2] = s3;
    vf[1][3] = 0.0f;
    vf[2][0] = -s3;
    vf[2][1] = 0.0f;
    vf[2][2] = c3;
    vf[2][3] = 0.0f;
    for (i = 0; i < 4; i++) {
        vf[3][i] = vf[28][i] * vf[1][0] + vf[29][i] * vf[1][1] + vf[30][i] * vf[1][2] + vf[31][i] * vf[1][3];
        vf[4][i] = vf[28][i] * vf[2][0] + vf[29][i] * vf[2][1] + vf[30][i] * vf[2][2] + vf[31][i] * vf[2][3];
    }
    for (i = 0; i < 4; i++) {
        vf[28][i] = vf[3][i];
        vf[30][i] = vf[4][i];
    }

    /* final: vf31.xyz = vin * basis (vmove.xyz); ACC keeps the three-term partial sum */
    for (i = 0; i < 4; i++) {
        vf[1][i] = vin[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = vf[28][i] * vf[1][0] + vf[29][i] * vf[1][1] + vf[30][i] * vf[1][2];
    }
    for (i = 0; i < 4; i++) {
        vf[2][i] = acc[i] + vf[31][i] * vf[1][3];
    }
    for (i = 0; i < 3; i++) {
        vf[31][i] = vf[2][i];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = acc[i];
    }
}
