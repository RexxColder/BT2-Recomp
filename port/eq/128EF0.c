#include "common.h"
#include "vu0_state.h"

/* 0x00128EF0: vsqi vf16..vf19 to VU data memory at vi15, vi15 incremented after each store. */
void func_00128EF0(void) {
    s32 k;

    for (k = 0; k < 4; k++) {
        memcpy(&gVu0.mem[(gVu0.vi[15] & 0xFF) * 16], gVu0.vf[16 + k], 16);
        gVu0.vi[15] = (gVu0.vi[15] + 1) & 0xFFFF;
    }
}
