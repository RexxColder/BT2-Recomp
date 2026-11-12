#include "common.h"
#include "vu0_state.h"

/* Vu0View_StoreMtx(a0): store vf28..vf31 to a0 +0x0, +0x10, +0x20, +0x30. */
void Vu0View_StoreMtx(u8 *arg0) {
    memcpy(arg0 + 0x00, gVu0.vf[28], 16);
    memcpy(arg0 + 0x10, gVu0.vf[29], 16);
    memcpy(arg0 + 0x20, gVu0.vf[30], 16);
    memcpy(arg0 + 0x30, gVu0.vf[31], 16);
}
