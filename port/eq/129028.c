#include "common.h"
#include "vu0_state.h"

/* 0x00129028: vf4 = load(a0); vf19.xyz += vf4.xyz. */
void func_00129028(u8 *arg0) {
    s32 i;

    memcpy(gVu0.vf[4], arg0, 16);
    for (i = 0; i < 3; i++) {
        gVu0.vf[19][i] = gVu0.vf[19][i] + gVu0.vf[4][i];
    }
}
