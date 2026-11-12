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

/* 0x00129FE0 Mtx_ProjectPoints(out, m, pts, n): the matrix rows m[0..3] (vf4..vf7) read from memory; for each of n
 * points at pts (16 bytes): p = m0 * x + m1 * y + m2 * z + m3 * w, q = 1 / p.w, p.xyz *= q; out (16 bytes) =
 * { int(x*16), int(y*16), int(z), int(w) }; on-screen flags as in Vu0Cur_ProjectPoints. Returns 1 when every
 * point passed, 0 at the first failure (its output is still stored). */
s32 Mtx_ProjectPoints(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 *src = arg2;
    s32 *dst = arg0;
    s32 n = arg3;
    f32 p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    s32 o[4] = { 0, 0, 0, 0 };
    f32 q = 0.0f;
    f32 d1;
    f32 d2;
    s32 bad;
    s32 c;
    s32 ok;

    do {
        for (c = 0; c < 4; c++) {
            p[c] = arg1[0 * 4 + c] * src[0] + arg1[1 * 4 + c] * src[1] + arg1[2 * 4 + c] * src[2] +
                   arg1[3 * 4 + c] * src[3];
        }
        q = 1.0f / p[3];
        p[0] = p[0] * q;
        p[1] = p[1] * q;
        p[2] = p[2] * q;

        VU0_TOI(p[0], 4, o[0]);
        VU0_TOI(p[1], 4, o[1]);
        VU0_TOI(p[2], 0, o[2]);
        VU0_TOI(p[3], 0, o[3]);
        for (c = 0; c < 4; c++) {
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
        src += 4;
        dst += 4;
    } while (n != 0);

    for (c = 0; c < 4; c++) {
        gVu0.vf[9][c] = p[c];
        memcpy(&gVu0.vf[10][c], &o[c], 4);
        gVu0.vf[11][c] = 0.0f;
    }
    gVu0.vf[12][0] = 4096.0f;
    gVu0.vf[12][1] = 4096.0f;
    gVu0.q = q;
    return ok;
}
