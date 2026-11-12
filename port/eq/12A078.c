#include "common.h"
#include "vu0_state.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);

/* VU0 vftoi, as in Vu0Cur_ProjectPoints: truncating, saturating, 'shift' fraction bits. */
#define VU0_TOI(f, shift, out)                                                     \
    do {                                                                           \
        double d_ = (double)(f) * (double)(1 << (shift));                          \
        u32 b_;                                                                    \
        memcpy(&b_, &(f), 4);                                                      \
        if (d_ != d_) {                                                            \
            (out) = (b_ & 0x80000000u) ? (s32)0x80000000u : 0x7FFFFFFF;            \
        } else if (d_ >= 2147483648.0) {                                           \
            (out) = 0x7FFFFFFF;                                                    \
        } else if (d_ <= -2147483648.0) {                                          \
            (out) = (s32)0x80000000u;                                              \
        } else {                                                                   \
            (out) = (s32)d_;                                                       \
        }                                                                          \
    } while (0)

#define VU0_ZERO_OR_NEG(f) ({ u32 b_; memcpy(&b_, &(f), 4); ((b_ & 0x7FFFFFFFu) == 0) | (s32)(b_ >> 31); })

/* 0x0012A078: project one point p (vec4) by the matrix rows m[0..3] (vf4..vf7, read from memory): q = (m rows
 * combined) with w = m3.w ... vf9 = m0 * p.x + m1 * p.y + m2 * p.z + m3 * p.w, Q = 1 / vf9.w, xyz * Q;
 * out (a0) = { int(x*16), int(y*16), int(z), int(w) }; stq (a1) = (uv.x * Q, uv.y * Q, vf13.z * Q, uv.w).
 * Returns 1 when the on-screen flags are clear (see Vu0Cur_ProjectPoints). */
s32 func_0012A078(s32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 *m = arg2;
    f32 *p = arg3;
    f32 *uv = arg4;
    f32 v9[4];
    f32 v3[4];
    s32 o[4];
    f32 q;
    f32 d1;
    f32 d2;
    s32 bad;
    s32 c;

    for (c = 0; c < 4; c++) {
        v9[c] = m[0 * 4 + c] * p[0] + m[1 * 4 + c] * p[1] + m[2 * 4 + c] * p[2];
        v9[c] = v9[c] + m[3 * 4 + c] * p[3];
    }
    q = 1.0f / v9[3];
    for (c = 0; c < 3; c++) {
        v9[c] = v9[c] * q;
    }
    v3[0] = uv[0] * q;
    v3[1] = uv[1] * q;
    v3[2] = gVu0.vf[13][2] * q;
    v3[3] = uv[3];

    VU0_TOI(v9[0], 4, o[0]);
    VU0_TOI(v9[1], 4, o[1]);
    VU0_TOI(v9[2], 0, o[2]);
    VU0_TOI(v9[3], 0, o[3]);
    for (c = 0; c < 4; c++) {
        arg0[c] = o[c];
        arg1[c] = v3[c];
    }

    d1 = 4096.0f - v9[0];
    d2 = 4096.0f - v9[1];
    bad = VU0_ZERO_OR_NEG(v9[0]) | VU0_ZERO_OR_NEG(v9[1]) | VU0_ZERO_OR_NEG(v9[3]) | VU0_ZERO_OR_NEG(d1) |
          VU0_ZERO_OR_NEG(d2);

    for (c = 0; c < 4; c++) {
        gVu0.vf[9][c] = v9[c];
        gVu0.vf[3][c] = v3[c];
        memcpy(&gVu0.vf[10][c], &o[c], 4);
        gVu0.vf[11][c] = 0.0f;
    }
    gVu0.vf[12][0] = 4096.0f;
    gVu0.vf[12][1] = 4096.0f;
    gVu0.q = q;
    return bad == 0;
}
