#include "common.h"
#include "vu0_state.h"

/* 0x00128758: vf13 = vf0 rotated, vf14 = vf13 rotated, vf15 = vf14 rotated (vmr32). */
void func_00128758(void) {
    f32 t[4];

    t[0] = gVu0.vf[0][1]; t[1] = gVu0.vf[0][2]; t[2] = gVu0.vf[0][3]; t[3] = gVu0.vf[0][0];
    memcpy(gVu0.vf[13], t, 16);
    t[0] = gVu0.vf[13][1]; t[1] = gVu0.vf[13][2]; t[2] = gVu0.vf[13][3]; t[3] = gVu0.vf[13][0];
    memcpy(gVu0.vf[14], t, 16);
    t[0] = gVu0.vf[14][1]; t[1] = gVu0.vf[14][2]; t[2] = gVu0.vf[14][3]; t[3] = gVu0.vf[14][0];
    memcpy(gVu0.vf[15], t, 16);
}
