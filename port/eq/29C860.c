#include "common.h"
#include "vu0_state.h"

/* Vu0Clip_LoadMtx(a0): vf20..vf23 = rows at a0 +0x0, +0x10, +0x20, +0x30. */
void Vu0Clip_LoadMtx(u8 *arg0) {
    memcpy(gVu0.vf[20], arg0 + 0x00, 16);
    memcpy(gVu0.vf[21], arg0 + 0x10, 16);
    memcpy(gVu0.vf[22], arg0 + 0x20, 16);
    memcpy(gVu0.vf[23], arg0 + 0x30, 16);
}
