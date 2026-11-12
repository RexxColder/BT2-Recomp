#include "common.h"

u64 BtlText_GetTex0(s32 part);
extern f32 D_003876C0;

/* GS packet builder: writes one 10-doubleword block (text tag, GS registers, two quads) at out and
 * returns the advanced pointer; returns out unchanged for the out-of-range cases, NULL when s1 <= 0. */
u64 *func_00108780(u64 *arg0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    u64 *out = arg0;
    s32 absT0;
    s64 s1;
    s64 s2;
    s64 s3;
    s64 s4;
    s64 s5;
    s64 s6;
    s64 a0v;
    s64 a1v;
    s64 a2v;
    s64 a3v;
    s64 v0;
    f32 f0;

    absT0 = (t0 < 0) ? -t0 : t0;
    s4 = (s32)((u32)(a1 + 0x700) << 4);
    s3 = (s32)((u32)(a1 + a3 + 0x700) << 4);
    s1 = (s32)((u32)(a2 + 0x720) << 4);
    s2 = (s32)((u32)(a2 + t0 + 0x720) << 4);
    s5 = (s32)((u32)absT0 << 4);
    s6 = (s32)((u32)a3 << 4);

    if (s4 <= 0) {
        return out;
    }
    if (s3 > 0xFFFF) {
        return out;
    }
    if (s1 <= 0) {
        return NULL;
    }
    if (s2 > 0xFFFF) {
        return out;
    }

    out[1] = 0x535316F0ULL;
    out[0] = 0x8400000000008001ULL;
    out[2] = 0x156ULL;
    out[3] = 0;
    out[4] = BtlText_GetTex0(t1);

    f0 = D_003876C0 * 128.0f;
    v0 = (s64)(s32)(f0);

    a1v = ((s64)s1 << 16) | s4 | (s64)0x0FFFFFFF00000000ULL;
    a2v = ((s64)s2 << 16) | s3 | (s64)0x0FFFFFFF00000000ULL;
    a0v = (s64)0x3F80000000000000ULL | v0 | ((v0 << 16) | 0x80000000LL) | (v0 << 8);
    a3v = s6 | (s5 << 16);

    out[5] = (u64)a0v;
    out[7] = (u64)a1v;
    out[6] = 0;
    out[8] = (u64)a3v;
    out[9] = (u64)a2v;
    return out + 10;
}
