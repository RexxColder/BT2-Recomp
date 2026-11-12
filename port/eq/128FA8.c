#include "common.h"
#include "vu0_state.h"

/* 0x00128FA8: store vf16..vf19 to a0 +0x0, +0x10, +0x20, +0x30. */
void func_00128FA8(u8 *arg0) {
    memcpy(arg0 + 0x00, gVu0.vf[16], 16);
    memcpy(arg0 + 0x10, gVu0.vf[17], 16);
    memcpy(arg0 + 0x20, gVu0.vf[18], 16);
    memcpy(arg0 + 0x30, gVu0.vf[19], 16);
}
