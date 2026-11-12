#include "common.h"

/* 0x001296A0 ClipVtx_SetArray: count = t0 (5th argument); per element copies 16 bytes from each of a1, a2, a3 to
 * a0 + 0x00, +0x10, +0x20 and advances a0 by 0x30. Nothing is copied when count is 0 (do-while on the count). */
void func_001296A0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4) {
    s32 k;

    if (arg4 == 0) {
        return;
    }
    do {
        for (k = 0; k < 16; k++) {
            arg0[k] = arg1[k];
            arg0[0x10 + k] = arg2[k];
            arg0[0x20 + k] = arg3[k];
        }
        arg1 += 16;
        arg2 += 16;
        arg3 += 16;
        arg0 += 0x30;
        arg4--;
    } while (arg4 != 0);
}
