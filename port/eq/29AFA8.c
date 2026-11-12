#include "common.h"

extern f32 D_00387284;
extern f32 D_00387288;
extern f32 D_0038728C;
extern f32 D_00387290;
extern f32 D_00387294;
extern f32 D_00387298;

s32 func_003126C8(s32 arg0, s32 arg1);
s32 func_00312680(s32 arg0, s32 arg1, f32 farg0);
f32 func_0029DFD0(s32 arg0);
f32 Mathf_Asin(f32 x);
f32 Mathf_Acos(f32 x);
f32 cosf(f32 x);

/* cvt.w.s truncates toward zero; values >= 2^31 are split and the top bit is set back */
#define FIX_U32(dst, x) do { \
    f32 fx_ = (x); \
    if (fx_ >= 2147483648.0f) { \
        (dst) = (u32)(s32)(fx_ - 2147483648.0f) | 0x80000000u; \
    } else { \
        (dst) = (u32)(s32)fx_; \
    } \
} while (0)

u64 func_0029AFA8(u8 *arg0) {
    f32 l[4];
    f32 m[4];
    f32 theta;
    f32 asn;
    f32 cs;
    f32 t;
    f32 f;
    f32 ax;
    u64 signs;
    s32 i;
    u32 a;
    u32 b;
    u32 c;
    u32 k;
    s32 v0;
    u32 s0;

    func_003126C8((s32)l, (s32)arg0);
    if (l[3] < 0.0f) {
        l[3] = -l[3];
        l[0] = -l[0];
        l[1] = -l[1];
        l[2] = -l[2];
    }

    func_003126C8((s32)m, (s32)l);
    m[3] = 0.0f;
    f = func_0029DFD0((s32)m);
    if (D_00387284 < f) {
        func_00312680((s32)m, (s32)m, 1.0f / f);
    } else {
        m[0] = 1.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
    }

    signs = 0;
    for (i = 0; i < 3; i++) {
        if (m[i] < 0.0f) {
            signs |= (u64)(1u << i);
        }
        ax = __builtin_fabsf(m[i]);
        m[i] = ax;
        if (1.0f < ax) {
            m[i] = 1.0f;
        }
    }

    asn = Mathf_Asin(m[1]);
    cs = cosf(asn);
    if (cs < D_00387288) {
        theta = 0.0f;
    } else {
        t = m[0] / cs;
        if (1.0f < t) {
            t = 1.0f;
        }
        theta = Mathf_Acos(t);
    }

    FIX_U32(a, asn * D_0038728C * D_00387290 + 0.5f);
    k = 0x7FFF - a;
    v0 = (s32)(k << 1);
    if (v0 >= 0) {
        f = theta * D_00387294 * (f32)v0;
    } else {
        f = theta * D_00387294 * (2.0f * (f32)(s32)((u32)v0 >> 1));
    }

    FIX_U32(b, f + 0.5f);
    s0 = k * k + b;

    f = __builtin_sqrtf(__builtin_fabsf(1.0f - l[3]));
    if (f < 0.0f) {
        f = 0.0f;
    }

    FIX_U32(c, f * D_00387298);

    return (signs << 61) | (((u64)s0 << 32) >> 1) | (u64)c;
}
