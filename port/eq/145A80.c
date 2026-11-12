#include "common.h"
#include "vu0_state.h"

/* 0x00145A80: VU0 vclipw.xyz of the vector at a0 against its w; returns the six new clip bits (x+, x-, y+, y-, z+, z-).
 * GUESS: bit order (the original reads them from vi18 with andi 0x3F). */
s32 func_00145A80(f32 *arg0) {
    f32 w;
    s32 flags = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = arg0[i];
    }
    w = gVu0.vf[1][3];
    for (i = 0; i < 3; i++) {
        if (gVu0.vf[1][i] > w) {
            flags |= 1 << (i * 2);
        }
        if (gVu0.vf[1][i] < -w) {
            flags |= 1 << (i * 2 + 1);
        }
    }
    return flags & 0x3F;
}
