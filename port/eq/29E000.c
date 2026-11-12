#include "common.h"

/* 0x0029E000: |a - b| over xyz (vsub, vmul, vaddy, vaddz, vsqrt of the absolute value). Pure: it ran on the PS2Recomp
   fallback until now. */
f32 Vec3_Dist(void *a0, void *a1) {
    f32 *a = (f32 *)a0, *b = (f32 *)a1;
    f32 dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];

    return __builtin_sqrtf(__builtin_fabsf((dx * dx + dy * dy) + dz * dz));
}
