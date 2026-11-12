#include "common.h"
#include "vu0_state.h"

/* Vec4_Sub(out a0, a a1, b a2): out = a - b on four lanes. */
void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    memcpy(gVu0.vf[5], arg2, 16);
    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] - gVu0.vf[5][i];
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
