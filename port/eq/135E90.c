#include "common.h"
#include "vu0_state.h"

/* IVec4_ToFloat12(out a0, in a1): out = (f32)in / 4096 per lane (int bits in memory). */
void IVec4_ToFloat12(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 v;

    memcpy(gVu0.vf[4], arg1, 16);
    for (i = 0; i < 4; i++) {
        memcpy(&v, &gVu0.vf[4][i], 4);
        gVu0.vf[5][i] = (f32)v / 4096.0f;
    }
    memcpy(arg0, gVu0.vf[5], 16);
}
