#include "common.h"
#include "vu0_state.h"

/* 0x00129E50: distance |a - b| over xyz, the same steps as func_00129E08 (vf15.x from gVu0). */
f32 func_00129E50(u8 *a0, void *a1) {
    f32 *a = (f32 *)a0, *b = (f32 *)a1;
    f32 dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];

    gVu0.acc[0] = dx * dx + dy * dy;
    gVu0.vf[4][0] = gVu0.acc[0] + gVu0.vf[15][0] * (dz * dz);
    gVu0.q = __builtin_sqrtf(__builtin_fabsf(gVu0.vf[4][0]));
    return gVu0.q;
}
