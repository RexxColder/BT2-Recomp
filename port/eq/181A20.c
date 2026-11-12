#include "common.h"

void func_00180440(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* 0x00181A20: for each of arg2 records of 0x30 bytes at arg1: copy floats +0x00..+0x20 and bytes +0x28..+0x2D to a frame,
 * frame+0x2E = arg3, frame+0x2F = arg4, then func_00180440(arg0, frame, rec[0x28], rec[0x29], rec[0x2A], rec[0x2B]). */
void func_00181A20(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 frame[0x30];
    u8 *r;
    s32 n;
    s32 k;

    r = arg1;
    for (n = arg2; n > 0; n--) {
        for (k = 0; k <= 0x20; k += 4) {
            *(f32 *)(frame + k) = *(f32 *)(r + k);
        }
        for (k = 0x28; k <= 0x2D; k++) {
            frame[k] = r[k];
        }
        frame[0x2E] = (u8)arg3;
        frame[0x2F] = (u8)arg4;
        func_00180440((u8 *)arg0, frame, r[0x28], r[0x29], r[0x2A], r[0x2B]);
        r += 0x30;
    }
}
