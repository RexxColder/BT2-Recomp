#include "common.h"
#include "vu0_state.h"

/* Vec3_AddSub(out a0, a a1, b a2, c a3): out.xyz = a + b - c, out.w = a.w. */
void Vec3_AddSub(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    memcpy(gVu0.vf[5], arg2, 16);
    memcpy(gVu0.vf[6], arg3, 16);
    for (i = 0; i < 3; i++) {
        gVu0.acc[i] = gVu0.vf[4][i] + gVu0.vf[5][i];
    }
    for (i = 0; i < 3; i++) {
        gVu0.vf[4][i] = gVu0.acc[i] - gVu0.vf[6][i] * gVu0.vf[0][3];
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
