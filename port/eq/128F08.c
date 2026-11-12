#include "common.h"
#include "vu0_state.h"

/* 0x00128F08: vlqd vf19..vf16 from VU data memory, vi15 decremented before each load. */
void func_00128F08(void) {
    s32 k;

    for (k = 0; k < 4; k++) {
        gVu0.vi[15] = (gVu0.vi[15] - 1) & 0xFFFF;
        memcpy(gVu0.vf[19 - k], &gVu0.mem[(gVu0.vi[15] & 0xFF) * 16], 16);
    }
}
