#include "common.h"

/* 0x001AFD08: VU0 transform of the 4 vectors at a1 by the vector a2 (vmulax/vmadday/vmaddaz, vmaddw with vf0.w = 1),
 * perspective divide by w (Q = 1 / w, xyz * Q), then a0 = { xy as int(x*16), int(y*16), int(z), int(w) }. */
void func_001AFD08(s32 *arg0, f32 *arg1, f32 *arg2) {
    f32 acc[4];
    f32 v6[4];
    f32 q;
    s32 i;

    for (i = 0; i < 4; i++) {
        acc[i] = arg1[i] * arg2[0];
        acc[i] = acc[i] + arg1[4 + i] * arg2[1];
        acc[i] = acc[i] + arg1[8 + i] * arg2[2];
        v6[i] = acc[i] + arg1[12 + i];
    }
    q = 1.0f / v6[3];
    for (i = 0; i < 3; i++) {
        v6[i] = v6[i] * q;
    }
    arg0[0] = (s32)(v6[0] * 16.0f);
    arg0[1] = (s32)(v6[1] * 16.0f);
    arg0[2] = (s32)v6[2];
    arg0[3] = (s32)v6[3];
}
