#include "common.h"
#include "vu0_state.h"

/* 0x00128FC0: Vu0Cur_GetTrans: store vf19 (16 bytes) at 0(arg0). */
void Vu0Cur_GetTrans(u8 *arg0) {
    f32 *dst = (f32 *)arg0;
    s32 i;

    for (i = 0; i < 4; i++) {
        dst[i] = gVu0.vf[19][i];
    }
}
