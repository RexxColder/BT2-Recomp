#include "common.h"

extern f32 sqrtf(f32 farg0);
void BtlOpp_GetDelta(s32 arg0, s32 arg1);

/* 0x00210A48: v = BtlOpp_GetDelta(arg0) (out buffer of 4 floats); returns sqrtf(v[0] * v[0] + v[2] * v[2]). */
f32 func_00210A48(s32 arg0) {
    f32 v[4];
    f32 sum;

    BtlOpp_GetDelta(arg0, (s32)v);
    sum = v[0] * v[0];
    sum = sum + v[2] * v[2];
    return sqrtf(sum);
}
