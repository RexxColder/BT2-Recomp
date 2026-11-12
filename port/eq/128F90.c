#include "common.h"
#include "vu0_state.h"

/* 0x00128F90: vf16..vf19 = load from a0 +0x0, +0x10, +0x20, +0x30. */
void func_00128F90(u8 *arg0) {
    memcpy(gVu0.vf[16], arg0 + 0x00, 16);
    memcpy(gVu0.vf[17], arg0 + 0x10, 16);
    memcpy(gVu0.vf[18], arg0 + 0x20, 16);
    memcpy(gVu0.vf[19], arg0 + 0x30, 16);
}
