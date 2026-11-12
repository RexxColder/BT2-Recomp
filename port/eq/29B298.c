#include "common.h"

extern f32 D_0038729C;
extern f32 D_003872A0;
extern f32 D_003872A4;

s32 func_00299AE0(s32 arg0);
f32 cosf(f32 x);
s32 func_003126C8(void *arg0, void *arg1);

/* 0x0029B298: builds a 3-vector from a 64-bit seed and writes it (scaled) to arg0 via func_003126C8.
   Fields of arg1: s0 = bits 31..60 (30 bits), mask = bits 61..63 (3 bits: negate vec[i] when bit i set),
   lo = low 31 bits of the low word, x = lo * 2^-31, w = 1 - x*x.
   Negative 32-bit intermediates are converted as unsigned halves (the R5900 has no unsigned cvt). */
s32 func_0029B298(void *arg0, u64 arg1) {
    f32 vec[3];
    f32 out[4];
    f32 x;
    f32 w;
    f32 f3;
    f32 f2a;
    f32 f2b;
    f32 f1b;
    f32 f12;
    f32 c1;
    f32 c2;
    f32 f20;
    f32 f21;
    f32 sy;
    f32 f1;
    s32 s0;
    s32 v10;
    s32 a0v;
    s32 a1v;
    s32 v0v;
    u32 mask;
    s32 lo;
    s32 i;

    s0 = (s32)((arg1 >> 31) & 0x3FFFFFFFULL);
    mask = (u32)(arg1 >> 61);
    lo = (s32)((u32)arg1 & 0x7FFFFFFFu);

    x = (f32)lo * 0x1p-31f;
    w = 1.0f - x * x;

    v10 = func_00299AE0(s0);
    a0v = (s32)((u32)s0 - (u32)v10 * (u32)v10);
    a1v = 0x7FFF - v10;
    v0v = (s32)((u32)v10 << 1);

    /* f2a = float(a1v) (unsigned-half conversion when negative) */
    if (a1v >= 0) {
        f2a = (f32)a1v;
    } else {
        f2a = (f32)(((u32)a1v >> 1) | ((u32)a1v & 1u)) * 2.0f;
    }
    /* f2b = float(a0v) */
    if (a0v >= 0) {
        f2b = (f32)a0v;
    } else {
        f2b = (f32)(((u32)a0v >> 1) | ((u32)a0v & 1u)) * 2.0f;
    }
    /* f1b = float(v0v) */
    if (v0v >= 0) {
        f1b = (f32)v0v;
    } else {
        f1b = (f32)(((u32)v0v >> 1) | ((u32)v0v & 1u)) * 2.0f;
    }

    f12 = (f2a * D_0038729C) * D_003872A0;
    f1 = f2b * (1.0f / f1b);
    f20 = f1 * D_003872A4;

    c1 = cosf(f12);
    f21 = __builtin_sqrtf(__builtin_fabsf(1.0f - c1 * c1));
    c2 = cosf(f20);
    sy = __builtin_sqrtf(__builtin_fabsf(1.0f - c2 * c2));

    vec[0] = c2 * c1;
    vec[1] = f21;
    vec[2] = sy * c1;

    for (i = 0; i < 3; i++) {
        if ((mask & (1u << i)) != 0) {
            vec[i] = -vec[i];
        }
    }

    f3 = __builtin_sqrtf(__builtin_fabsf(1.0f - w * w));

    out[0] = vec[0] * f3;
    out[1] = vec[1] * f3;
    out[2] = vec[2] * f3;
    out[3] = w; /* sp+0xC keeps the spilled w = 1 - x*x; func_003126C8 copies all 16 bytes */

    return func_003126C8(arg0, out);
}
