#include "common.h"
#include "vu0_state.h"

/* 0x0029C8A8: vf31 = (0,0,0,1) (vsub then vadd.w), vf30, vf29, vf28 rotated copies (identity rows). */
void func_0029C8A8(void) {
    s32 i;
    f32 t[4];

    for (i = 0; i < 4; i++) {
        gVu0.vf[31][i] = gVu0.vf[0][i] - gVu0.vf[0][i];
    }
    gVu0.vf[31][3] = gVu0.vf[31][3] + gVu0.vf[0][3];
    t[0] = gVu0.vf[31][1]; t[1] = gVu0.vf[31][2]; t[2] = gVu0.vf[31][3]; t[3] = gVu0.vf[31][0];
    memcpy(gVu0.vf[30], t, 16);
    t[0] = gVu0.vf[30][1]; t[1] = gVu0.vf[30][2]; t[2] = gVu0.vf[30][3]; t[3] = gVu0.vf[30][0];
    memcpy(gVu0.vf[29], t, 16);
    t[0] = gVu0.vf[29][1]; t[1] = gVu0.vf[29][2]; t[2] = gVu0.vf[29][3]; t[3] = gVu0.vf[29][0];
    memcpy(gVu0.vf[28], t, 16);
}
