#include "common.h"
#include "vu0_state.h"

/* 0x00129E08: |v| of the xyz of a 4-float vector: ACC.x = x*x + y*y; vf4.x = ACC.x + vf15.x * z*z; Q = sqrt.
   vf15 is the (1, 0, 0, 0) basis func_00128758 keeps in gVu0; on the fallback it was the recompiler's own vf15. */
f32 func_00129E08(u8 *arg0) {
    f32 *v = (f32 *)arg0;
    f32 x = v[0] * v[0], y = v[1] * v[1], z = v[2] * v[2];

    gVu0.acc[0] = x + y;
    gVu0.vf[4][0] = gVu0.acc[0] + gVu0.vf[15][0] * z;
    gVu0.q = __builtin_sqrtf(__builtin_fabsf(gVu0.vf[4][0]));
    return gVu0.q;
}
