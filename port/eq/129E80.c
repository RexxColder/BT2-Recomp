#include "common.h"

/* 0x00129E80 Vec3_DistSq: ((dx*dx + dy*dy) + dz*dz) with d = a - b on xyz (VU0 vsub / vmul / vadda / vmadd). */
f32 Vec3_DistSq(f32 *arg0, f32 *arg1) {
    f32 dx = arg0[0] - arg1[0];
    f32 dy = arg0[1] - arg1[1];
    f32 dz = arg0[2] - arg1[2];
    f32 xx = dx * dx;
    f32 yy = dy * dy;
    f32 zz = dz * dz;

    return (xx + yy) + zz;
}
