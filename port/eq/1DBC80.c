#include "common.h"

/* 0x001DBC80 (v, a, b): VU0 vsqrt(|v . (b - a)|) over xyz, summed (x + y) + z. Pure: it ran on the PS2Recomp
   fallback until now. */
f32 func_001DBC80(void *a0, void *a1, void *a2) {
    f32 *v = (f32 *)a0, *a = (f32 *)a1, *b = (f32 *)a2;

    return __builtin_sqrtf(__builtin_fabsf((v[0] * (b[0] - a[0]) + v[1] * (b[1] - a[1])) + v[2] * (b[2] - a[2])));
}
