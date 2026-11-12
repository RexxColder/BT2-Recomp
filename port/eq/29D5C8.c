#include "common.h"
#include "vu0_state.h"

/* Vu0View_LoadMtx(a0): vf28..vf31 = rows at a0 +0x0, +0x10, +0x20, +0x30. */
void Vu0View_LoadMtx(u8 *arg0) {
    memcpy(gVu0.vf[28], arg0 + 0x00, 16);
    memcpy(gVu0.vf[29], arg0 + 0x10, 16);
    memcpy(gVu0.vf[30], arg0 + 0x20, 16);
    memcpy(gVu0.vf[31], arg0 + 0x30, 16);
}
