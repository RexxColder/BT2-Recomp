#include "common.h"

extern f32 D_0038725C;
extern f32 D_00387260;
extern f32 D_00387264;
extern f32 D_00387268;
extern f32 D_0038726C;
extern f32 D_00387270;

void func_003126C8(void *arg0, void *arg1);
void func_00312680(void *arg0, void *arg1, f32 farg0);
f32 func_0029DFD0(s32 arg0);
f32 Mathf_Asin(f32 arg0);
f32 Mathf_Acos(f32 farg0);
f32 cosf(f32 farg0);

/* 0x0029A9A0 (direction encoder). Copies the vec4 at arg0, flips it when w < 0, takes a unit direction of its xyz
 * (or (1, 0, 0) when the length is not above D_0038725C), clamps the absolute components to 1 and packs them: the
 * sign bits of the three components (bit i for component i, shifted to bit 29), the two angle indices built from
 * asin of y and acos of x (ratio clamped to 1), and the sqrt(1 - w) term. */
u32 func_0029A9A0(u8 *arg0) {
    f32 v[4];
    f32 w[4];
    f32 len;
    f32 asinY;
    f32 cosA;
    f32 ratio;
    f32 angle = 0.0f;
    f32 t0;
    f32 t1;
    f32 f0;
    f32 f1;
    s32 signs = 0;
    s32 i;
    s32 v1a;
    s32 v1b;
    s32 a0;
    s32 v0;
    s32 s0;
    u32 packed;

    func_003126C8(v, arg0);
    if (v[3] < 0.0f) {
        v[0] = -v[0];
        v[1] = -v[1];
        v[2] = -v[2];
        v[3] = -v[3];
    }

    func_003126C8(w, v);
    w[3] = 0.0f;
    len = func_0029DFD0((s32)w);
    if (D_0038725C < len) {
        func_00312680(w, w, 1.0f / len);
    } else {
        w[2] = 0.0f;
        w[0] = 1.0f;
        w[1] = 0.0f;
    }

    for (i = 0; i < 3; i++) {
        f0 = w[i];
        if (f0 < 0.0f) {
            signs = signs | (1 << i);
        }
        f1 = __builtin_fabsf(f0);
        w[i] = f1;
        if (1.0f < f1) {
            w[i] = 1.0f;
        }
    }

    asinY = Mathf_Asin(w[1]);
    cosA = cosf(asinY);
    if (!(cosA < D_00387260)) {
        ratio = w[0] / cosA;
        if (1.0f < ratio) {
            ratio = 1.0f;
        }
        angle = Mathf_Acos(ratio);
    }

    t0 = (asinY * D_00387264) * D_00387268 + 0.5f;
    if (2147483648.0f <= t0) {
        v1a = (s32)(t0 - 2147483648.0f) | (s32)0x80000000;
    } else {
        v1a = (s32)t0;
    }
    a0 = 0x1FF - v1a;

    v0 = a0 << 1;
    f1 = angle * D_0038726C;
    if (v0 >= 0) {
        f1 = f1 * (f32)v0;
    } else {
        v0 = (s32)((u32)v0 >> 1);
        f0 = (f32)v0;
        f0 = f0 + f0;
        f1 = f1 * f0;
    }

    t1 = f1 + 0.5f;
    if (2147483648.0f <= t1) {
        v1b = (s32)(t1 - 2147483648.0f) | (s32)0x80000000;
    } else {
        v1b = (s32)t1;
    }

    s0 = (a0 * a0) + v1b;

    f0 = 1.0f - w[3];
    f0 = __builtin_sqrtf(f0);
    f1 = f0;
    if (f1 < 0.0f) {
        f1 = 0.0f;
    }
    f0 = f1 * D_00387270;
    if (2147483648.0f <= f0) {
        a0 = (s32)(f0 - 2147483648.0f) | (s32)0x80000000;
    } else {
        a0 = (s32)f0;
    }

    packed = ((u32)signs << 29) | ((u32)s0 << 11) | (u32)a0;
    return packed;
}
