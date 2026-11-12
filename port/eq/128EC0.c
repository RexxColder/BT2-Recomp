#include "common.h"
#include "vu0_state.h"

/* Vu0Cur_Init: vf19 = vf0, then vf18, vf17, vf16 rotated copies (identity rows); vi15 = 0. */
void Vu0Cur_Init(void) {
    f32 t[4];

    memcpy(gVu0.vf[19], gVu0.vf[0], 16);
    t[0] = gVu0.vf[19][1]; t[1] = gVu0.vf[19][2]; t[2] = gVu0.vf[19][3]; t[3] = gVu0.vf[19][0];
    memcpy(gVu0.vf[18], t, 16);
    t[0] = gVu0.vf[18][1]; t[1] = gVu0.vf[18][2]; t[2] = gVu0.vf[18][3]; t[3] = gVu0.vf[18][0];
    memcpy(gVu0.vf[17], t, 16);
    t[0] = gVu0.vf[17][1]; t[1] = gVu0.vf[17][2]; t[2] = gVu0.vf[17][3]; t[3] = gVu0.vf[17][0];
    memcpy(gVu0.vf[16], t, 16);
    gVu0.vi[15] = 0;
}
