#include "common.h"

void *memset(void *dst, s32 c, u32 n);
f32 sqrtf(f32 arg0);
f32 atan2f(f32 arg0, f32 arg1);

extern f32 D_00387008;
extern f32 D_0038700C;
extern f32 D_00387010;
extern f32 D_00387014;

/* 0x002762F0: yaw from a point to a target (x/z plane). Normalizes (dx, 1, dz) (zero when the length is not
 * positive), takes atan2 of x and z, minus pi, and wraps the result into [-pi, pi]. */
f32 Stg_CalcYaw(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 d[4];
    f32 dx;
    f32 dz;
    f32 sum;
    f32 len;
    f32 a;

    dx = x0 - x1;
    dz = z0 - z1;
    memset(d, 0, 16);
    d[0] = dx;
    d[1] = 1.0f;
    d[3] = 1.0f;
    d[2] = dz;

    sum = dx * dx;
    sum = sum + 1.0f;
    sum = sum + dz * dz;
    len = sqrtf(sum);
    if (0.0f < len) {
        d[0] = d[0] / len;
        d[1] = d[1] / len;
        d[2] = d[2] / len;
    } else {
        d[0] = 0.0f;
        d[1] = 0.0f;
        d[2] = 0.0f;
    }

    a = atan2f(d[0], d[2]) - D_00387008;
    if (D_00387008 < a) {
        a = a - D_0038700C;
    }
    if (a < D_00387010) {
        a = a + D_00387014;
    }
    return a;
}
