#include "common.h"
#include "vu0_state.h"

/* 0x001A7818: squared distance between two vectors, xyz only: ((dx*dx + dy*dy) + dz*dz) (VU0 vsub.xyzw / vmul / vadd). */
f32 func_001A7818(f32 *arg0, f32 *arg1) {
    f32 dx = arg0[0] - arg1[0];
    f32 dy = arg0[1] - arg1[1];
    f32 dz = arg0[2] - arg1[2];
    f32 xx = dx * dx;
    f32 yy = dy * dy;
    f32 zz = dz * dz;

    return (xx + yy) + zz;
}
