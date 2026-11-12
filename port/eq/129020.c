#include "common.h"
#include "vu0_state.h"

/* 0x00129020: Vu0Cur_SetTrans: load vf19 (16 bytes) from 0(arg0). */
void Vu0Cur_SetTrans(u8 *arg0) {
    f32 *src = (f32 *)arg0;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[19][i] = src[i];
    }
}
