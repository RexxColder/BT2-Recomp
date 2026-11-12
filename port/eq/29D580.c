#include "common.h"
#include "vu0_state.h"

extern s32 D_00387DB0;
extern u8 D_0038B100[] __attribute__((section(".data")));

/* 0x0029D580: D_00387DB0 -= arg0; loads the 4x4 matrix number D_00387DB0 (64 bytes each) into vf28..vf31 (VU0 lqc2). */
void func_0029D580(s32 arg0) {
    s32 i;
    s32 r;
    f32 *m;

    D_00387DB0 = D_00387DB0 - arg0;
    m = (f32 *)(D_0038B100 + (D_00387DB0 << 6));
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            gVu0.vf[28 + r][i] = m[r * 4 + i];
        }
    }
}
