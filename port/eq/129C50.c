#include "common.h"

/* 0x00129C50 Mtx_MulVec4: arg0 = m * v for the 4x4 matrix at arg1 (rows 0..3, 16 bytes each) and the vector arg2:
 * component i = ((m0[i]*v.x + m1[i]*v.y) + m2[i]*v.z) + m3[i]*v.w (VU0 vmulax / vmadday / vmaddaz / vmaddw). */
void Mtx_MulVec4(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 acc[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        acc[i] = arg1[i] * arg2[0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + arg1[4 + i] * arg2[1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + arg1[8 + i] * arg2[2];
    }
    for (i = 0; i < 4; i++) {
        arg0[i] = acc[i] + arg1[12 + i] * arg2[3];
    }
}
