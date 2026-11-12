#include "common.h"
#include "vu0_state.h"

/* 0x00128790: store vf0 (16 bytes) at 0x30(arg0). */
void func_00128790(u8 *arg0) {
    f32 *dst = (f32 *)(arg0 + 0x30);
    s32 i;

    for (i = 0; i < 4; i++) {
        dst[i] = gVu0.vf[0][i];
    }
}
