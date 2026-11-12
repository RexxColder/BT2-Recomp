#include "common.h"
#include "vu0_state.h"

/* 0x00129C38(a0, a1): out.xyz = a1.xyz, out.w = a0.w (vmove.xyz into the stored vector). */
void func_00129C38(u8 *arg0, u8 *arg1) {
    s32 i;

    memcpy(gVu0.vf[4], arg1, 16);
    memcpy(gVu0.vf[5], arg0, 16);
    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.vf[4][i];
    }
    memcpy(arg0, gVu0.vf[5], 16);
}
