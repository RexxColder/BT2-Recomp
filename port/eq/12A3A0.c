#include "common.h"

/* 0x0012A3A0 Vec3_Add4: dst.xyz = ((a + b) + c) + d, dst.w = a.w (VU0 vadda / vmaddaw / vmaddw). */
void Vec3_Add4(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 i;

    for (i = 0; i < 3; i++) {
        f32 s = arg1[i] + arg2[i];

        s = s + arg3[i];
        arg0[i] = s + arg4[i];
    }
    arg0[3] = arg1[3];
}
