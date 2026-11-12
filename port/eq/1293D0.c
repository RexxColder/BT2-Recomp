#include "common.h"
#include "vu0_state.h"

/* 0x001293D0(a0, a1): vf4 = load(a1); ACC = vf16*x + vf17*y + vf18*z; vf4 = ACC + vf19*w; store vf4 to a0. */
void func_001293D0(u8 *arg0, u8 *arg1) {
    s32 i;
    f32 w;

    memcpy(gVu0.vf[4], arg1, 16);
    w = gVu0.vf[4][3];
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.vf[16][i] * gVu0.vf[4][0];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.acc[i] + gVu0.vf[17][i] * gVu0.vf[4][1];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.acc[i] + gVu0.vf[18][i] * gVu0.vf[4][2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[4][i] = gVu0.acc[i] + gVu0.vf[19][i] * w;
    }
    memcpy(arg0, gVu0.vf[4], 16);
}
