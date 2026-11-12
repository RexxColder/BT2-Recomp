#include "common.h"

f32 func_001146E0(s32 a0, s32 a1);
f32 sinf(f32 x);
f32 cosf(f32 x);

s64 *func_00114B10(s64 *arg0, s32 arg1, f32 farg0) {
    s64 *s2;
    s64 *s1;
    s32 s3;
    s32 s4;
    s32 si;
    s32 ci;
    s32 ti;
    s32 s0;
    s32 v;
    f32 t20;
    f32 t22;
    f32 sv;
    f32 cv;
    f32 dv;

    s3 = 0;
    arg0[0] = (s64)0xC400000000008001ULL;
    arg0[1] = (((s64)0x5555 << 16 | 0x5555) << 16) | 0xDD10;
    s2 = arg0 + 2;
    s2[0] = 0x45;
    s2[1] = (((s64)0x3F800000 << 16 | 0x500E) << 16) | 0xBB2D;
    s2 = s2 + 2;
    t22 = func_001146E0(arg1, 0x45);
    do {
        if (s3 == 0) {
            s2[0] = 0x80008000LL;
            s4 = 0;
        } else {
            s4 = s3 & 1;
            t20 = t22 + farg0 * (f32)(s3 - 5) * 0.25f;
            sv = sinf(t20) * 72.0f;
            ti = (s32)sv;
            dv = sv - (f32)ti;
            if (dv > 0.5f || (dv == 0.5f && (ti & 1))) {
                ti += 1;
            } else if (dv < -0.5f || (dv == -0.5f && (ti & 1))) {
                ti -= 1;
            }
            si = ti;
            cv = cosf(t20) * 72.0f;
            ti = (s32)cv;
            dv = cv - (f32)ti;
            if (dv > 0.5f || (dv == 0.5f && (ti & 1))) {
                ti += 1;
            } else if (dv < -0.5f || (dv == -0.5f && (ti & 1))) {
                ti -= 1;
            }
            ci = ti;
            s0 = 0x800 - si;
            v = 0x800 - ci;
            s1 = s2 + s4;
            *s1 = (s64)(s0 << 4) | ((s64)(v << 4) << 16);
        }
        s3 += 1;
        if (s4 != 0) {
            s2 = s2 + 2;
        }
    } while (s3 < 0xA);
    return s2;
}
