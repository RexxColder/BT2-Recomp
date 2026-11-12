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

/* 0x001295B8 (Vu0Cur_ProjectPointsStq-like): for each of n = t0 points at a2 (vec4) with uv at a3 (vec4): p = M * point
 * (gVu0 matrix), q = 1 / p.w, p.xyz *= q; out int (a0) = { int(x*16), int(y*16), int(z), int(w) }; stq (a1) =
 * (uv.x * q, uv.y * q, vf13.z * q, vf2.w as it stands). Returns 1 when every point passed (on-screen flags). */
s32 func_001295B8(s32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    f32 *pt = arg2;
    f32 *uv = arg3;
    s32 *dst = arg0;
    f32 *stq = arg1;
    s32 n = arg4;
    f32 p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    s32 o[4] = { 0, 0, 0, 0 };
    f32 s[4];
    f32 q = 0.0f;
    f32 d1;
    f32 d2;
    s32 bad;
    s32 c;
    s32 ok;

    for (;;) {
        for (c = 0; c < 4; c++) {
            p[c] = gVu0.vf[16][c] * pt[0] + gVu0.vf[17][c] * pt[1] + gVu0.vf[18][c] * pt[2] +
                   gVu0.vf[19][c] * pt[3];
        }
        q = 1.0f / p[3];
        p[0] = p[0] * q;
        p[1] = p[1] * q;
        p[2] = p[2] * q;
        s[0] = uv[0] * q;
        s[1] = uv[1] * q;
        s[2] = gVu0.vf[13][2] * q;
        s[3] = gVu0.vf[2][3];

        VU0_TOI(p[0], 4, o[0]);
        VU0_TOI(p[1], 4, o[1]);
        VU0_TOI(p[2], 0, o[2]);
        VU0_TOI(p[3], 0, o[3]);
        for (c = 0; c < 4; c++) {
            stq[c] = s[c];
            dst[c] = o[c];
        }

        d1 = 4096.0f - p[0];
        d2 = 4096.0f - p[1];
        bad = VU0_ZERO_OR_NEG(p[0]) | VU0_ZERO_OR_NEG(p[1]) | VU0_ZERO_OR_NEG(p[3]) | VU0_ZERO_OR_NEG(d1) |
              VU0_ZERO_OR_NEG(d2);
        if (bad) {
            ok = 0;
            break;
        }
        ok = 1;
        n -= 1;
        if (n == 0) {
            break;
        }
        pt += 4;
        uv += 4;
        dst += 4;
        stq += 4;
    }
    for (c = 0; c < 4; c++) {
        gVu0.vf[5][c] = p[c];
        gVu0.vf[2][c] = s[c];
        gVu0.vf[3][c] = s[c];
        gVu0.vf[11][c] = 0.0f;
    }
    gVu0.vf[12][0] = 4096.0f;
    gVu0.vf[12][1] = 4096.0f;
    gVu0.q = q;
    return ok;
}
