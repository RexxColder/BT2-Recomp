#include "common.h"

/* 0x00129CD8 Vec3_Dot: ((a.x*b.x + a.y*b.y) + a.z*b.z), VU0 vmul / vadda / vmadd with vf15.x = 1.0. */
f32 Vec3_Dot(f32 *arg0, f32 *arg1) {
    f32 xx = arg0[0] * arg1[0];
    f32 yy = arg0[1] * arg1[1];
    f32 zz = arg0[2] * arg1[2];

    return (xx + yy) + zz;
}
