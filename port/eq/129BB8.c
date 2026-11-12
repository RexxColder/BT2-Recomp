#include "common.h"
#include "vu0_state.h"

/* Vec4_Scale(out a0, a a1, f12 s): out = a * s on four lanes. */
void Vec4_Scale(u8 *arg0, u8 *arg1, f32 farg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    gVu0.vf[5][0] = farg0;
    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] * gVu0.vf[5][0];
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
