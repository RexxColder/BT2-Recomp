#include "common.h"
#include "vu0_state.h"

/* 0x0012D868: loads the matrix rows (vf4..vf7) from arg1. For each of count (arg3) iterations, with v = the vector at
 * arg2 (vf8) and u = the vector at arg5 (vf11): vf9 = M * v (rows vf4..vf7), Q = 1 / vf9.w, vf9.xyz *= Q,
 * vf12.xyz = u.xyz * Q (vf12.w keeps its old value). arg0 gets the integer words (x, y at 4 fraction bits, z and w
 * plain, truncated); arg4 gets vf12. Both output pointers and both input pointers advance by 16 bytes. */
void func_0012D868(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 *arg4, f32 *arg5) {
    s32 n = arg3;
    s32 i;
    f32 acc[4];
    f32 q;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = arg1[0 + i];   /* lqc2 vf4..vf7, 0x00..0x30(a1) */
        gVu0.vf[5][i] = arg1[4 + i];
        gVu0.vf[6][i] = arg1[8 + i];
        gVu0.vf[7][i] = arg1[12 + i];
    }

    do {
        for (i = 0; i < 4; i++) {
            gVu0.vf[8][i] = arg2[i];    /* lqc2 vf8, 0(a2) */
            gVu0.vf[11][i] = arg5[i];   /* lqc2 vf11, 0(t1) */
        }

        /* vmulax / vmadday / vmaddaz into ACC, vmaddw into vf9 */
        for (i = 0; i < 4; i++) {
            acc[i] = gVu0.vf[4][i] * gVu0.vf[8][0];
            acc[i] = acc[i] + gVu0.vf[5][i] * gVu0.vf[8][1];
            acc[i] = acc[i] + gVu0.vf[6][i] * gVu0.vf[8][2];
            gVu0.acc[i] = acc[i];
            gVu0.vf[9][i] = acc[i] + gVu0.vf[7][i] * gVu0.vf[8][3];
        }

        q = 1.0f / gVu0.vf[9][3];       /* vdiv Q, vf0.w, vf9.w */
        gVu0.q = q;
        for (i = 0; i < 3; i++) {
            gVu0.vf[9][i] = gVu0.vf[9][i] * q;     /* vmulq.xyz vf9, vf9, Q */
            gVu0.vf[12][i] = gVu0.vf[11][i] * q;   /* vmulq.xyz vf12, vf11, Q */
        }

        /* vftoi4.xyzw vf10, vf9 then vftoi0.zw overrides z and w */
        arg0[0] = (s32)(gVu0.vf[9][0] * 16.0f);
        arg0[1] = (s32)(gVu0.vf[9][1] * 16.0f);
        arg0[2] = (s32)gVu0.vf[9][2];
        arg0[3] = (s32)gVu0.vf[9][3];

        for (i = 0; i < 4; i++) {
            arg4[i] = gVu0.vf[12][i];   /* sqc2 vf12, 0(t0) */
        }

        arg2 += 4;
        arg0 += 4;
        arg4 += 4;
        arg5 += 4;
        n -= 1;
    } while (n != 0);
}
