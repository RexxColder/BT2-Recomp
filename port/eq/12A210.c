#include "common.h"
#include "vu0_state.h"

/* Sticky zero (0x40) / sign (0x80) flags of one written lane, as set by the VU0 vsub compares. */
#define VU0_STICKY(st, r) do { f32 vu0_r = (r); u32 vu0_b = *(u32 *)&vu0_r; \
    if ((vu0_b & 0x7FFFFFFF) == 0) { (st) |= 0x40; } \
    if (vu0_b & 0x80000000) { (st) |= 0x80; } } while (0)

/* 0x0012A210: three int vectors (a0, a1, a2) are converted with vitof4.xy (xy divided by 16) and vitof0.zw
 * (vf7, vf8, vf9). vf5.xy = 4096.0 (qmtc2 of 0x4580000045800000). Compares: vf0 = vf7/8/9 - 0 on xyw and
 * vf0 = vf5 - vf7/8/9 on xy. Returns 1 when all those lanes are positive (x, y, w in the GS range). */
s32 func_0012A210(s32 *arg0, s32 *arg1, s32 *arg2) {
    s32 *src[3];
    u32 st;
    s32 i;
    s32 j;

    src[0] = arg0;
    src[1] = arg1;
    src[2] = arg2;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            if (i < 2) {
                gVu0.vf[7 + j][i] = (f32)src[j][i] / 16.0f;
            } else {
                gVu0.vf[7 + j][i] = (f32)src[j][i];
            }
        }
    }

    gVu0.vf[5][0] = 4096.0f;
    gVu0.vf[5][1] = 4096.0f;

    st = 0;
    for (j = 0; j < 3; j++) {
        VU0_STICKY(st, gVu0.vf[7 + j][0]);
        VU0_STICKY(st, gVu0.vf[7 + j][1]);
        VU0_STICKY(st, gVu0.vf[7 + j][3]);
        VU0_STICKY(st, gVu0.vf[5][0] - gVu0.vf[7 + j][0]);
        VU0_STICKY(st, gVu0.vf[5][1] - gVu0.vf[7 + j][1]);
    }
    return (st & 0xC0) == 0;
}
