#include "common.h"
#include "vu0_state.h"

/* 0x00129970 ClipPlane_EdgeParam: farg0 / dot(p, q - a) on xyz (VU0 vsub.xyz / vmul.xyz / vadda.x / vmaddz.x with
 * vf15.x, then a float divide). */
f32 ClipPlane_EdgeParam(f32 *arg0, f32 *arg1, f32 *arg2, f32 farg0) {
    f32 d[3];
    f32 acc;
    f32 dot;
    s32 i;

    for (i = 0; i < 3; i++) {
        d[i] = arg1[i] - arg2[i];
    }
    for (i = 0; i < 3; i++) {
        d[i] = arg0[i] * d[i];
    }
    acc = d[0] + d[1];
    dot = acc + gVu0.vf[15][0] * d[2];
    return farg0 / dot;
}
