#include "common.h"
#include "vu0_state.h"

/* 0x00129F60: VU0 projection. vf8 = in (a2); vf4..vf7 = matrix columns (a1, 16 bytes each).
 * ACC = M*in (xyzw, vmulax/vmadday/vmaddaz), vf9 = ACC + col3 * in.w; Q = 1 / vf9.w (vdiv against vf0.w = 1);
 * vf9.xyz *= Q (vmulq); vf12.xy = 4096.0 (qmtc2 of 0x4580000045800000), vf11 = 0; vf10.xy = ftoi4(vf9.xy),
 * vf10.zw = ftoi0(vf9.zw) (sqc2 to a0). vi16 (STATUS) sticky zero / sign flags over the vsub compares (xyw of vf9, 4096 - vf9.xy) decide the return: 1 when clear. */
/* Sticky zero (0x40) / sign (0x80) flags of one written lane, as set by the VU0 vsub compares. */
#define VU0_STICKY(st, r) do { f32 vu0_r = (r); u32 vu0_b = *(u32 *)&vu0_r; \
    if ((vu0_b & 0x7FFFFFFF) == 0) { (st) |= 0x40; } \
    if (vu0_b & 0x80000000) { (st) |= 0x80; } } while (0)

s32 func_00129F60(s32 *a0, f32 *a1, f32 *a2) {
    s32 i;
    s32 j;
    f32 w;
    f32 q;
    u32 st;

    for (i = 0; i < 4; i++) {
        gVu0.vf[8][i] = a2[i];
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            gVu0.vf[4 + j][i] = a1[j * 4 + i];
        }
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.vf[4][i] * gVu0.vf[8][0];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.acc[i] + gVu0.vf[5][i] * gVu0.vf[8][1];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = gVu0.acc[i] + gVu0.vf[6][i] * gVu0.vf[8][2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[9][i] = gVu0.acc[i] + gVu0.vf[7][i] * gVu0.vf[8][3];
    }
    w = gVu0.vf[9][3];
    q = 1.0f / w;
    gVu0.q = q;
    for (i = 0; i < 4; i++) {
        gVu0.vf[11][i] = 0.0f;
    }
    gVu0.vf[12][0] = 4096.0f;
    gVu0.vf[12][1] = 4096.0f;
    gVu0.vf[12][2] = 0.0f;
    gVu0.vf[12][3] = 0.0f;
    for (i = 0; i < 3; i++) {
        gVu0.vf[9][i] = gVu0.vf[9][i] * q;
    }
    *(s32 *)&gVu0.vf[10][0] = (s32)(gVu0.vf[9][0] * 16.0f);
    *(s32 *)&gVu0.vf[10][1] = (s32)(gVu0.vf[9][1] * 16.0f);
    *(s32 *)&gVu0.vf[10][2] = (s32)gVu0.vf[9][2];
    *(s32 *)&gVu0.vf[10][3] = (s32)gVu0.vf[9][3];
    for (i = 0; i < 4; i++) {
        a0[i] = *(s32 *)&gVu0.vf[10][i];
    }
    st = 0;
    VU0_STICKY(st, gVu0.vf[9][0]);
    VU0_STICKY(st, gVu0.vf[9][1]);
    VU0_STICKY(st, gVu0.vf[9][3]);
    VU0_STICKY(st, 4096.0f - gVu0.vf[9][0]);
    VU0_STICKY(st, 4096.0f - gVu0.vf[9][1]);
    return (st & 0xC0) == 0;
}
