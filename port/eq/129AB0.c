#include "common.h"
#include "vu0_state.h"

/* 0x00129AB0: store vf0 (16 bytes) at 0(arg0). */
void func_00129AB0(u8 *arg0) {
    f32 *dst = (f32 *)arg0;
    s32 i;

    for (i = 0; i < 4; i++) {
        dst[i] = gVu0.vf[0][i];
    }
}
