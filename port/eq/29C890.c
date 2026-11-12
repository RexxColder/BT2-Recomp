#include "common.h"
#include "vu0_state.h"

/* 0x0029C890(a0): store vf20..vf23 to a0 +0x0, +0x10, +0x20, +0x30. */
void func_0029C890(u8 *arg0) {
    memcpy(arg0 + 0x00, gVu0.vf[20], 16);
    memcpy(arg0 + 0x10, gVu0.vf[21], 16);
    memcpy(arg0 + 0x20, gVu0.vf[22], 16);
    memcpy(arg0 + 0x30, gVu0.vf[23], 16);
}
