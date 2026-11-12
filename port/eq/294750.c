#include "common.h"

/* 0x00294750: |b - a| over xyz, summed as z*z + (x*x + y*y) (vmr32 / vadd), VU0 vsqrt of the absolute value.
   Pure: it ran on the PS2Recomp fallback until now. */
f32 ColB_Vec3Dist(void *a0, void *a1) {
    f32 *a = (f32 *)a0, *b = (f32 *)a1;
    f32 dx = b[0] - a[0], dy = b[1] - a[1], dz = b[2] - a[2];

    return __builtin_sqrtf(__builtin_fabsf(dz * dz + (dx * dx + dy * dy)));
}
