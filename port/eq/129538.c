#include "common.h"
#include "vu0_state.h"

/* Sticky zero (0x40) / sign (0x80) flags of one written lane, as set by the VU0 vsub compares. */
#define VU0_STICKY(st, r) do { f32 vu0_r = (r); u32 vu0_b = *(u32 *)&vu0_r; \
    if ((vu0_b & 0x7FFFFFFF) == 0) { (st) |= 0x40; } \
    if (vu0_b & 0x80000000) { (st) |= 0x80; } } while (0)

/* 0x00129538: vf5 = matrix (columns vf16..vf19) * in[0..3] (a2); q = 1 / vf5.w; xyz of vf5 divided by w.
 * vf3 = in2 (a3) with z taken from vf13.z, xyz scaled by q, stored to out2 (a1) as 16 bytes.
 * out[0..1] = trunc(x * 16), trunc(y * 16); out[2..3] = trunc(z), trunc(w) (vftoi4.xy / vftoi0.zw) to a0.
 * Returns 1 when every lane tested by the compares (vf5.xyw > 0, 4096 - vf5.xy > 0) is positive. */
s32 func_00129538(s32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 q;
    u32 st;
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[5][i] = gVu0.vf[16][i] * arg2[0] + gVu0.vf[17][i] * arg2[1]
                      + gVu0.vf[18][i] * arg2[2] + gVu0.vf[19][i] * arg2[3];
    }

    q = 1.0f / gVu0.vf[5][3];

    for (i = 0; i < 4; i++) {
        gVu0.vf[3][i] = arg3[i];
    }
    gVu0.vf[3][2] = gVu0.vf[13][2];

    for (i = 0; i < 3; i++) {
        gVu0.vf[5][i] = gVu0.vf[5][i] * q;
        gVu0.vf[3][i] = gVu0.vf[3][i] * q;
    }

    for (i = 0; i < 4; i++) {
        arg1[i] = gVu0.vf[3][i];
    }

    arg0[0] = (s32)(gVu0.vf[5][0] * 16.0f);
    arg0[1] = (s32)(gVu0.vf[5][1] * 16.0f);
    arg0[2] = (s32)gVu0.vf[5][2];
    arg0[3] = (s32)gVu0.vf[5][3];

    st = 0;
    VU0_STICKY(st, gVu0.vf[5][0]);
    VU0_STICKY(st, gVu0.vf[5][1]);
    VU0_STICKY(st, gVu0.vf[5][3]);
    VU0_STICKY(st, 4096.0f - gVu0.vf[5][0]);
    VU0_STICKY(st, 4096.0f - gVu0.vf[5][1]);
    return (st & 0xC0) == 0;
}
