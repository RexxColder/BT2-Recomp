#include "common.h"
#include "vu0_state.h"

/* 0x00128780: store vf15, vf14, vf13 to a0 +0x0, +0x10, +0x20. */
void func_00128780(u8 *arg0) {
    memcpy(arg0 + 0x00, gVu0.vf[15], 16);
    memcpy(arg0 + 0x10, gVu0.vf[14], 16);
    memcpy(arg0 + 0x20, gVu0.vf[13], 16);
}
