#include "common.h"
#include "vu0_state.h"

/* 0x00112818: arg2 times (do ... while, the count is tested after the decrement; arg2 = 0 runs the loop again and
 * wraps): out[0..3] = ftoi0(vf28*x + vf29*y + vf30*z + vf31 * vf0.w) with (x, y, z, w) = in[0..3], then out += 16,
 * in += 16. VU0 vmulax / vmadday / vmaddaz / vmaddw / vftoi0. */
void func_00112818(s32 *arg0, f32 *arg1, s32 arg2) {
    s32 *out = arg0;
    f32 *in = arg1;
    s32 n = arg2;
    f32 acc[4];
    s32 i;

    do {
        for (i = 0; i < 4; i++) {
            gVu0.vf[5][i] = in[i];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = gVu0.vf[28][i] * gVu0.vf[5][0];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = acc[i] + gVu0.vf[29][i] * gVu0.vf[5][1];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = acc[i] + gVu0.vf[30][i] * gVu0.vf[5][2];
        }
        for (i = 0; i < 4; i++) {
            gVu0.vf[6][i] = acc[i] + gVu0.vf[31][i] * gVu0.vf[0][3];
        }
        for (i = 0; i < 4; i++) {
            out[i] = (s32)gVu0.vf[6][i];
        }
        n = n - 1;
        out += 4;
        in += 4;
    } while (n != 0);
}
