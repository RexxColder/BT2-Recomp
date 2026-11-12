#include "common.h"
#include "vu0_state.h"

extern f32 D_0036D8E0[4] __attribute__((section(".data")));

/* 0x001286B8 Vu0_SinCos(angle in f12): vf12 = (sin, cos, z * 0, w * 0); the same routine as BT3's Vu0_SinCos
 * (Tenkaichi3Decomp src/port/vu0_a.c). u = pi/2 -+ angle; cos = u + c3 u^3 + c5 u^5 + c7 u^7 + c9 u^9 with the
 * coefficients at 0x36D8E0 = (c9, c7, c5, c3); sin = +-sqrt(1 - cos^2). Only right for |angle| <= pi.
 * It ran on the PS2Recomp fallback, whose VU0 registers are not gVu0: the C rotations (Mtx_RotateX/Y/Z) read a
 * stale vf12 and every effect rotated through them came out NaN (ki beams and blasts collapsed to one point). */
void func_001286B8(f32 angle) {
    const f32 *coef = (const f32 *)D_0036D8E0;
    const f32 halfPi = 1.57079637f; /* gp-relative constant (0x3FC90FDB) */
    s32 neg = angle < 0.0f;
    f32 u = neg ? halfPi + angle : halfPi - angle;
    f32 u2, v6[4], c, s;
    s32 k;

    gVu0.vf[4][0] = u;
    gVu0.vf[4][3] = u;                            /* vmr32.w vf4, vf4 */
    gVu0.vf[12][0] = 0.0f + u;
    u2 = u * u;
    gVu0.vf[4][0] = u2;
    gVu0.vf[12][1] *= 0.0f;                       /* vmulx.yzw vf12, vf12, vf0x */
    gVu0.vf[12][2] *= 0.0f;
    gVu0.vf[12][3] *= 0.0f;
    for (k = 0; k < 4; k++) {
        gVu0.vf[5][k] = coef[k];
        v6[k] = coef[k] * u;                      /* vmulw vf6, vf5, vf4w */
        v6[k] = v6[k] * u2;                       /* vmulx.xyzw */
    }
    for (k = 0; k < 3; k++) {
        v6[k] = v6[k] * u2;                       /* vmulx.xyz */
    }
    gVu0.vf[12][0] = gVu0.vf[12][0] + v6[3];
    v6[0] = v6[0] * u2;                           /* vmulx.xy */
    v6[1] = v6[1] * u2;
    gVu0.vf[12][0] = gVu0.vf[12][0] + v6[2];
    v6[0] = v6[0] * u2;                           /* vmulx.x */
    gVu0.vf[12][0] = gVu0.vf[12][0] + v6[1];
    gVu0.vf[12][0] = gVu0.vf[12][0] + v6[0];
    for (k = 0; k < 4; k++) {
        gVu0.vf[6][k] = v6[k];
    }
    c = 0.0f + gVu0.vf[12][0];
    gVu0.vf[12][0] = c;                           /* vaddx.xy vf12, vf0, vf12x */
    gVu0.vf[12][1] = c;
    gVu0.vf[7][0] = c * c;
    gVu0.vf[7][3] = 1.0f - gVu0.vf[7][0];
    gVu0.q = __builtin_sqrtf(__builtin_fabsf(gVu0.vf[7][3])); /* VU vsqrt takes the absolute value */
    s = 0.0f + gVu0.q;
    gVu0.vf[7][0] = s;
    gVu0.vf[12][0] = neg ? 0.0f - s : 0.0f + s;
}
