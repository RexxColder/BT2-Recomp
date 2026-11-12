#include "common.h"

/* 0x00121610: |a - b| over xyz (vsub, vmul, vaddy, vaddz, vsqrt of the absolute value). Pure: it ran on the PS2Recomp
   fallback until now. */
f32 func_00121610(void *a0, void *a1) {
    f32 *a = (f32 *)a0, *b = (f32 *)a1;
    f32 dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];

    return __builtin_sqrtf(__builtin_fabsf((dx * dx + dy * dy) + dz * dz));
}
