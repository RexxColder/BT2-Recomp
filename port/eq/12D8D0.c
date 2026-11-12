#include "common.h"

/* 0x0012D8D0 (dst, a, b, c): the unit normal of the triangle a, b, c: n = (b - a) x (c - a) (vopmula / vopmsub),
   len = vsqrt(|n.n|), dst = (n * (1 / len), 0) (vdiv Q = vf0w / len). Pure: it ran on the PS2Recomp fallback. */
void func_0012D8D0(void *dst, void *a1, void *a2, void *a3) {
    f32 *a = (f32 *)a1, *b = (f32 *)a2, *c = (f32 *)a3, *o = (f32 *)dst;
    f32 u[3], v[3], n[3], len, q;

    u[0] = b[0] - a[0]; u[1] = b[1] - a[1]; u[2] = b[2] - a[2];
    v[0] = c[0] - a[0]; v[1] = c[1] - a[1]; v[2] = c[2] - a[2];
    n[0] = u[1] * v[2] - v[1] * u[2];
    n[1] = u[2] * v[0] - v[2] * u[0];
    n[2] = u[0] * v[1] - v[0] * u[1];
    len = __builtin_sqrtf(__builtin_fabsf((n[0] * n[0] + n[1] * n[1]) + n[2] * n[2]));
    q = 1.0f / len;
    o[0] = n[0] * q;
    o[1] = n[1] * q;
    o[2] = n[2] * q;
    o[3] = 0.0f;
}
