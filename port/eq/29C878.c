#include "common.h"
#include "vu0_state.h"

/* 0x0029C878(a0): store vf24..vf27 to a0 +0x0, +0x10, +0x20, +0x30. */
void func_0029C878(u8 *arg0) {
    memcpy(arg0 + 0x00, gVu0.vf[24], 16);
    memcpy(arg0 + 0x10, gVu0.vf[25], 16);
    memcpy(arg0 + 0x20, gVu0.vf[26], 16);
    memcpy(arg0 + 0x30, gVu0.vf[27], 16);
}
