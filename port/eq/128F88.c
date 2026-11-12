#include "common.h"
#include "vu0_state.h"

/* 0x00128F88: Vu0Cur_ClearTrans: vf19 = vf0. */
void Vu0Cur_ClearTrans(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[19][i] = gVu0.vf[0][i];
    }
}
