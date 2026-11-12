#include "common.h"
#include "vu0_state.h"

/* 0x0029D680: cur (vf28..vf31, copied to vf1..vf4) becomes m * cur: row i = ((c0 * m[i][0] + c1 * m[i][1]) +
 * c2 * m[i][2]) + c3 * m[i][3], lane by lane, with m's rows loaded to vf5..vf8. */
void func_0029D680(f32 *arg0) {
    f32 old[4][4];
    s32 r;
    s32 i;

    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            old[r][i] = gVu0.vf[28 + r][i];
            gVu0.vf[1 + r][i] = old[r][i];
            gVu0.vf[5 + r][i] = arg0[r * 4 + i];
        }
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            gVu0.acc[i] = old[0][i] * arg0[r * 4 + 0];
            gVu0.acc[i] = gVu0.acc[i] + old[1][i] * arg0[r * 4 + 1];
            gVu0.acc[i] = gVu0.acc[i] + old[2][i] * arg0[r * 4 + 2];
            gVu0.vf[28 + r][i] = gVu0.acc[i] + old[3][i] * arg0[r * 4 + 3];
        }
    }
}
