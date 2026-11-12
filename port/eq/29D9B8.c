#include "common.h"
#include "vu0_state.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);

/* 0x0029D9B8(vec, ang): VU0 macro code, the same as 0x0029D2D8 with the rotations in the order Z (ang[2]),
 * X (ang[0]), Y (ang[1]). vf1 = *vec; vf31 = M * vf1 first. Each rotation uses a 4 x 4 stack block. */
#define MUL_COL(dst, src)                                                                                    \
    for (i = 0; i < 4; i++) {                                                                                \
        gVu0.vf[dst][i] = gVu0.vf[28][i] * gVu0.vf[src][0] + gVu0.vf[29][i] * gVu0.vf[src][1] +              \
                          gVu0.vf[30][i] * gVu0.vf[src][2] + gVu0.vf[31][i] * gVu0.vf[src][3];               \
    }

void func_0029D9B8(f32 *arg0, f32 *arg1) {
    f32 st[16];
    s32 i;
    f32 c;
    f32 s;

    memcpy(gVu0.vf[1], arg0, 16);
    MUL_COL(2, 1);
    for (i = 0; i < 4; i++) {
        gVu0.vf[31][i] = gVu0.vf[2][i];
    }

    /* rotation about Z by ang[2] */
    st[0] = 1.0f; st[1] = 0.0f; st[2] = 0.0f; st[3] = 0.0f;
    st[4] = 0.0f; st[5] = 1.0f; st[6] = 0.0f; st[7] = 0.0f;
    st[8] = 0.0f; st[9] = 0.0f; st[10] = 1.0f; st[11] = 0.0f;
    st[12] = 0.0f; st[13] = 0.0f; st[14] = 0.0f; st[15] = 1.0f;
    c = cosf(arg1[2]);
    s = sinf(arg1[2]);
    st[0] = c;
    st[1] = -s;
    st[4] = s;
    st[5] = c;
    memcpy(gVu0.vf[1], &st[0], 16);
    memcpy(gVu0.vf[2], &st[4], 16);
    MUL_COL(4, 1);
    MUL_COL(3, 2);
    for (i = 0; i < 4; i++) {
        gVu0.vf[28][i] = gVu0.vf[4][i];
        gVu0.vf[29][i] = gVu0.vf[3][i];
    }

    /* rotation about X by ang[0] */
    st[0] = 1.0f; st[1] = 0.0f; st[2] = 0.0f; st[3] = 0.0f;
    st[4] = 0.0f; st[5] = 1.0f; st[6] = 0.0f; st[7] = 0.0f;
    st[8] = 0.0f; st[9] = 0.0f; st[10] = 1.0f; st[11] = 0.0f;
    st[12] = 0.0f; st[13] = 0.0f; st[14] = 0.0f; st[15] = 1.0f;
    c = cosf(arg1[0]);
    s = sinf(arg1[0]);
    st[5] = c;
    st[6] = -s;
    st[9] = s;
    st[10] = c;
    memcpy(gVu0.vf[1], &st[4], 16);
    memcpy(gVu0.vf[2], &st[8], 16);
    MUL_COL(3, 1);
    MUL_COL(4, 2);
    for (i = 0; i < 4; i++) {
        gVu0.vf[29][i] = gVu0.vf[3][i];
        gVu0.vf[30][i] = gVu0.vf[4][i];
    }

    /* rotation about Y by ang[1] */
    st[0] = 1.0f; st[1] = 0.0f; st[2] = 0.0f; st[3] = 0.0f;
    st[4] = 0.0f; st[5] = 1.0f; st[6] = 0.0f; st[7] = 0.0f;
    st[8] = 0.0f; st[9] = 0.0f; st[10] = 1.0f; st[11] = 0.0f;
    st[12] = 0.0f; st[13] = 0.0f; st[14] = 0.0f; st[15] = 1.0f;
    c = cosf(arg1[1]);
    s = sinf(arg1[1]);
    st[0] = c;
    st[2] = -s;
    st[8] = s;
    st[10] = c;
    memcpy(gVu0.vf[1], &st[0], 16);
    memcpy(gVu0.vf[2], &st[8], 16);
    MUL_COL(3, 1);
    MUL_COL(4, 2);
    for (i = 0; i < 4; i++) {
        gVu0.vf[28][i] = gVu0.vf[3][i];
        gVu0.vf[30][i] = gVu0.vf[4][i];
    }
}
