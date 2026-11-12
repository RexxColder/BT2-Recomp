#include "common.h"
#include "vu0_state.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);

/* VU0 vftoi: out = float f -> int with 'shift' fraction bits, truncating, saturating. */
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

/* 1 when the value is zero or has its sign bit set (the sticky Z / S clip-test flags). */
#define VU0_ZERO_OR_NEG(f) ({ u32 b_; memcpy(&b_, &(f), 4); ((b_ & 0x7FFFFFFFu) == 0) | (s32)(b_ >> 31); })

/* 0x001294B0 Vu0Cur_ProjectPoints(out, in, n): for each of n points at in (vec4, 16 bytes): p = M * point with
 * M = the current matrix (gVu0.vf[16..19] as columns), q = 1 / p.w, p.xyz *= q; out = { int(x*16), int(y*16),
 * int(z), int(w) }; the point is on screen when x, y, w and 4096 - x, 4096 - y all test nonzero and positive.
 * Returns 1 when every point passed, 0 at the first one that failed (its output is still stored).
 * VU0 state written back: vf5 (last projected point), vf6 (last output bits), vf11 = 0, vf12.xy = 4096, Q. */
s32 Vu0Cur_ProjectPoints(s32 *arg0, f32 *arg1, s32 arg2) {
    f32 *src = arg1;
    s32 *dst = arg0;
    s32 n = arg2;
    s32 last[4] = { 0, 0, 0, 0 };
    f32 p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    f32 q = 0.0f;
    f32 d1;
    f32 d2;
    s32 bad;
    s32 c;
    s32 ok;

    for (;;) {
        for (c = 0; c < 4; c++) {
            p[c] = gVu0.vf[16][c] * src[0] + gVu0.vf[17][c] * src[1] + gVu0.vf[18][c] * src[2] +
                   gVu0.vf[19][c] * src[3];
        }
        q = 1.0f / p[3];
        p[0] = p[0] * q;
        p[1] = p[1] * q;
        p[2] = p[2] * q;

        VU0_TOI(p[0], 4, dst[0]);
        VU0_TOI(p[1], 4, dst[1]);
        VU0_TOI(p[2], 0, dst[2]);
        VU0_TOI(p[3], 0, dst[3]);
        for (c = 0; c < 4; c++) {
            last[c] = dst[c];
        }

        d1 = 4096.0f - p[0];
        d2 = 4096.0f - p[1];
        bad = VU0_ZERO_OR_NEG(p[0]) | VU0_ZERO_OR_NEG(p[1]) | VU0_ZERO_OR_NEG(p[3]) |
              VU0_ZERO_OR_NEG(d1) | VU0_ZERO_OR_NEG(d2);
        if (bad) {
            ok = 0;
            break;
        }
        ok = 1;
        n -= 1;
        if (n == 0) {
            break;
        }
        src += 4;
        dst += 4;
    }

    for (c = 0; c < 4; c++) {
        gVu0.vf[5][c] = p[c];
        memcpy(&gVu0.vf[6][c], &last[c], 4);
        gVu0.vf[11][c] = 0.0f;
    }
    gVu0.vf[12][0] = 4096.0f;
    gVu0.vf[12][1] = 4096.0f;
    gVu0.q = q;
    return ok;
}
