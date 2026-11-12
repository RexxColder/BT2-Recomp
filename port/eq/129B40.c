#include "common.h"
#include "vu0_state.h"

/* Vec3_Add(out a0, a a1, b a2): out.xyz = a + b, out.w = a.w. */
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    memcpy(gVu0.vf[5], arg2, 16);
    for (i = 0; i < 3; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] + gVu0.vf[5][i];
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
