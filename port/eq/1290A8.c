#include "common.h"
#include "vu0_state.h"

/* 0x001290A8 Vu0Cur_MulMtx(m): the current matrix (vf16..vf19 rows) becomes m * cur. Each new row r is
 * ((cur0 * m[r][0] + cur1 * m[r][1]) + cur2 * m[r][2]) + cur3 * m[r][3], lane by lane, all four lanes, using
 * the OLD rows (copied to vf8..vf11 first). vf4..vf7 hold m's rows and ACC keeps the last partial sum. */
void Vu0Cur_MulMtx(f32 *m) {
    f32 old[4][4];
    f32 acc[4];
    s32 r;
    s32 i;

    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            old[r][i] = gVu0.vf[16 + r][i];
            gVu0.vf[8 + r][i] = old[r][i];   /* vmove.xyzw vf8..vf11, vf16..vf19 */
            gVu0.vf[4 + r][i] = m[r * 4 + i]; /* lqc2 vf4..vf7, 0x00..0x30(a0) */
        }
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            acc[i] = old[0][i] * m[r * 4 + 0];
            acc[i] = acc[i] + old[1][i] * m[r * 4 + 1];
            acc[i] = acc[i] + old[2][i] * m[r * 4 + 2];
            gVu0.vf[16 + r][i] = acc[i] + old[3][i] * m[r * 4 + 3];
        }
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = acc[i];
    }
}
