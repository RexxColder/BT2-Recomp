#include "common.h"
#include "vu0_state.h"

extern s32 D_00387DB0;
extern u8 D_0038B100[] __attribute__((section(".data")));

/* 0x0029D548: stores the matrix vf28..vf31 (64 bytes) at D_0038B100 + 64 * D_00387DB0, then D_00387DB0 += 1. */
void func_0029D548(void) {
    s32 idx = D_00387DB0;
    f32 *m = (f32 *)(D_0038B100 + idx * 64);
    s32 r;
    s32 i;

    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            m[r * 4 + i] = gVu0.vf[28 + r][i];
        }
    }
    D_00387DB0 = idx + 1;
}
