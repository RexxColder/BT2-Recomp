#include "common.h"
#include "vu0_state.h"

/* 0x0029C8C0: VU0 transform of the vector at a0 by the matrix in vf28..vf31:
 *   acc = vf28*x + vf29*y + vf30*z (vmulax / vmadday / vmaddaz), vf2 = acc + vf31*w (vmaddw), then vf31 = vf2. */
void func_0029C8C0(f32 *arg0) {
    f32 acc[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = arg0[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[28][i] * gVu0.vf[1][0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[29][i] * gVu0.vf[1][1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[30][i] * gVu0.vf[1][2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = acc[i];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[2][i] = acc[i] + gVu0.vf[31][i] * gVu0.vf[1][3];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[31][i] = gVu0.vf[2][i];
    }
}
