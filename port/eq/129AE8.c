#include "common.h"
#include "vu0_state.h"

extern f32 sqrtf(f32 farg0);

/* 0x00129AE8: normalizes the vector at a1 into a0 (VU0 vmul.xyz, vadda.x, vmaddz.x with vf15.x, vrsqrt into Q,
 * vmulq.xyz; w is kept). */
void func_00129AE8(f32 *arg0, f32 *arg1) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = arg1[i];
    }
    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.vf[4][i] * gVu0.vf[4][i];
    }
    gVu0.acc[0] = gVu0.vf[5][0] + gVu0.vf[5][1];
    gVu0.vf[5][0] = gVu0.acc[0] + gVu0.vf[15][0] * gVu0.vf[5][2];
    /* PS2 VU0: 1/0 gives the maximum float (there is no Inf) and 0 * max = 0. On the host 1/0 = +Inf and
     * 0 * Inf = NaN: a zero-length direction (the beam on its first frame) turned every beam node into NaN. */
    if (gVu0.vf[5][0] > 0.0f) {
        gVu0.q = 1.0f / sqrtf(gVu0.vf[5][0]);
    } else if (gVu0.vf[5][0] == 0.0f) {
        gVu0.q = 3.4028234663852886e+38f; /* VU0 value for 1/0; xyz are all zero, so the product stays 0 */
    } else {
        gVu0.q = __builtin_nanf(""); /* NaN in -> NaN out, as on the PS2 */
    }
    for (i = 0; i < 3; i++) {
        gVu0.vf[4][i] = gVu0.vf[4][i] * gVu0.q;
    }
    for (i = 0; i < 4; i++) {
        arg0[i] = gVu0.vf[4][i];
    }
}
