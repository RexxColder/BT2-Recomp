#include "common.h"
#include "vu0_state.h"

/* Vu0Cur_TranslateLocal(a0): vf4 = load(a0); ACC = vf16*x + vf17*y + vf18*z; vf19 = ACC + vf19*w. */
void Vu0Cur_TranslateLocal(u8 *arg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg0, 16);
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
        gVu0.vf[19][i] = gVu0.acc[i] + gVu0.vf[19][i] * gVu0.vf[4][3];
    }
}
