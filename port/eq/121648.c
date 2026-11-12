#include "common.h"

/* 0x00121648: |a - b| over x and z only (vsub.xyz, vmul.xyz, then vaddz.x: the y term is never added): the distance
   on the ground plane. Pure: it ran on the PS2Recomp fallback until now. */
f32 func_00121648(void *a0, void *a1) {
    f32 *a = (f32 *)a0, *b = (f32 *)a1;
    f32 dx = a[0] - b[0], dz = a[2] - b[2];

    return __builtin_sqrtf(__builtin_fabsf(dx * dx + dz * dz));
}
