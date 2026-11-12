#include "common.h"
#include "vu0_state.h"

/* 0x00129380: vf4 = load(a0); vf16.x *= vf4.x; vf17.y *= vf4.y; vf18.z *= vf4.z. */
void func_00129380(u8 *arg0) {
    memcpy(gVu0.vf[4], arg0, 16);
    gVu0.vf[16][0] = gVu0.vf[16][0] * gVu0.vf[4][0];
    gVu0.vf[17][1] = gVu0.vf[17][1] * gVu0.vf[4][1];
    gVu0.vf[18][2] = gVu0.vf[18][2] * gVu0.vf[4][2];
}
