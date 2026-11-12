#include "common.h"
#include "vu0_state.h"

/* Vu0Screen_LoadMtx(a0): vf24..vf27 = rows at a0 +0x0, +0x10, +0x20, +0x30. */
void Vu0Screen_LoadMtx(u8 *arg0) {
    memcpy(gVu0.vf[24], arg0 + 0x00, 16);
    memcpy(gVu0.vf[25], arg0 + 0x10, 16);
    memcpy(gVu0.vf[26], arg0 + 0x20, 16);
    memcpy(gVu0.vf[27], arg0 + 0x30, 16);
}
