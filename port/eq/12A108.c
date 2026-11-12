#include "common.h"
#include "vu0_state.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);

/* 0x0012A108(out_int, out_f, m, in, p, count): transforms count vertices. vf4..vf7 = the 4 rows of m (as the
 * asm loads them), vf8 = in, vf9 = m * vf8, Q = 1 / vf9.w, vf9.xyz *= Q, vf2.xyz = vf3.xyz * Q (vf3.z = vf13.z),
 * vf10 = (ftoi4(x), ftoi4(y), ftoi0(z), ftoi0(w)). Stores vf2 then vf10 and stops early when the sticky Z/S flags
 * of the on-screen test are set (x, y, w, 4096-x, 4096-y), returning 0; returns 1 when all counted vertices pass. */
#define VU0_BAD(v) ((v) == 0.0f || (v) < 0.0f)
#define VU0_FTOI(c, shift, out) { \
    double _d = (double)(c) * (double)(1 << (shift)); \
    if (_d >= 2147483648.0) { (out) = 0x7FFFFFFF; } \
    else if (_d <= -2147483648.0) { (out) = (s32)0x80000000u; } \
    else { (out) = (s32)_d; } }

s32 func_0012A108(void *a0, void *a1, void *a2, void *a3, void *t0, s32 t1) {
    u8 *pa0 = (u8 *)a0;
    u8 *pa1 = (u8 *)a1;
    u8 *pa3 = (u8 *)a3;
    u8 *pv1 = (u8 *)t0;
    s32 i10[4];
    s32 k;
    s32 bad;
    f32 acc;
    f32 q;

    memcpy(gVu0.vf[4], a2, 64);
    memcpy(gVu0.vf[8], pa3, 16);
    memcpy(gVu0.vf[3], pv1, 16);
    do {
        for (k = 0; k < 4; k++) {
            acc = gVu0.vf[4][k] * gVu0.vf[8][0];
            acc = acc + gVu0.vf[5][k] * gVu0.vf[8][1];
            acc = acc + gVu0.vf[6][k] * gVu0.vf[8][2];
            gVu0.vf[9][k] = acc + gVu0.vf[7][k] * gVu0.vf[8][3];
        }
        q = 1.0f / gVu0.vf[9][3];
        gVu0.vf[3][2] = gVu0.vf[13][2];
        pa3 += 16;
        pv1 += 16;
        memcpy(gVu0.vf[8], pa3, 16);
        for (k = 0; k < 3; k++) {
            gVu0.vf[9][k] = gVu0.vf[9][k] * q;
            gVu0.vf[2][k] = gVu0.vf[3][k] * q;
        }
        memcpy(gVu0.vf[3], pv1, 16);
        bad = VU0_BAD(gVu0.vf[9][0]) || VU0_BAD(gVu0.vf[9][1]) || VU0_BAD(gVu0.vf[9][3]) ||
              VU0_BAD(4096.0f - gVu0.vf[9][0]) || VU0_BAD(4096.0f - gVu0.vf[9][1]);
        VU0_FTOI(gVu0.vf[9][0], 4, i10[0]);
        VU0_FTOI(gVu0.vf[9][1], 4, i10[1]);
        VU0_FTOI(gVu0.vf[9][2], 0, i10[2]);
        VU0_FTOI(gVu0.vf[9][3], 0, i10[3]);
        memcpy(pa1, gVu0.vf[2], 16);
        memcpy(pa0, i10, 16);
        pa0 += 16;
        if (bad) {
            return 0;
        }
        pa1 += 16;
        t1 -= 1;
    } while (t1 != 0);
    return 1;
}
