#include "common.h"

/* 0x00177510: |v| over xyz: x*x + y*y, + z*z, VU0 vsqrt (absolute value) of the sum. Pure: it ran on the PS2Recomp
   fallback until now. */
f32 func_00177510(void *a0) {
    f32 *v = (f32 *)a0;

    return __builtin_sqrtf(__builtin_fabsf((v[0] * v[0] + v[1] * v[1]) + v[2] * v[2]));
}
