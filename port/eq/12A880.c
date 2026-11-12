#include "common.h"

void sceVu0InterVector(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

/* One lane: values >= 2^31 are converted from (x - 2^31) and get the sign bit set. */
static s32 lane_to_int(f32 x)
{
    if (x >= 2147483648.0f) {
        return (s32)((u32)(s32)(x - 2147483648.0f) | 0x80000000u);
    }
    return (s32)x;
}

/* 0x0012A880: blends 256 pairs of 4-byte vectors (A from srcA, B from srcB) with
 * sceVu0InterVector at weight t (clamped to 0..1). Lane c of pair i is stored at
 * dst[4*i + c]. Returns the converted lane 3 of the last pair. */
s32 func_0012A880(u8 *dst, u8 *srcA, u8 *srcB, f32 t)
{
    f32 va[4];
    f32 vb[4];
    f32 vo[4];
    s32 i;
    s32 wv = 0;
    u8 *out;

    if (t < 0.0f) {
        t = 0.0f;
    }
    if (1.0f < t) {
        t = 1.0f;
    }

    i = 0;
    do {
        va[0] = (f32)srcA[0];
        va[1] = (f32)srcA[1];
        va[2] = (f32)srcA[2];
        va[3] = (f32)srcA[3];
        srcA += 4;

        vb[0] = (f32)srcB[0];
        vb[1] = (f32)srcB[1];
        vb[2] = (f32)srcB[2];
        vb[3] = (f32)srcB[3];
        srcB += 4;

        sceVu0InterVector((s32)vo, (s32)va, (s32)vb, t);

        out = dst + 4 * i;
        out[0] = (u8)lane_to_int(vo[0]);
        out[1] = (u8)lane_to_int(vo[1]);
        out[2] = (u8)lane_to_int(vo[2]);
        wv = lane_to_int(vo[3]);
        out[3] = (u8)wv;
        i++;
    } while (i < 256);

    return wv;
}
