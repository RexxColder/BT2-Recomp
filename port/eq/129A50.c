#include "common.h"
#include "vu0_state.h"

/* 0x00129A50: for each of arg3 (>= 1) 0x30-byte records at arg2 (vector v8 = record[0..3], vector v3 = record[4..7]):
 * v9 = v8 * M, M = gVu0 rows 16..19; q = 1 / v9.w; v3.z = gVu0.vf[13].z; v9.xyz *= q; v2.xyz = v3.xyz * q (w kept
 * from gVu0.vf[2]); arg0 (ints) = { (s32)(v9.x*16), (s32)(v9.y*16), (s32)v9.z, (s32)v9.w }; arg1 = v2.
 * Advances arg0 by 0x10 and arg1 by 0x10 per record. The VU state (vf2, vf3, vf8, vf9, vf10, Q) is written back. */
void func_00129A50(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 *src = arg2;
    f32 v8[4];
    f32 v3[4];
    f32 v9[4];
    f32 v2[4];
    s32 v10[4];
    f32 q = 0.0f;
    s32 count = arg3;
    s32 i;

    for (i = 0; i < 4; i++) {
        v8[i] = src[i];
        v3[i] = src[4 + i];
        v2[i] = gVu0.vf[2][i];
    }
    do {
        for (i = 0; i < 4; i++) {
            v9[i] = gVu0.vf[16][i] * v8[0];
            v9[i] = v9[i] + gVu0.vf[17][i] * v8[1];
            v9[i] = v9[i] + gVu0.vf[18][i] * v8[2];
            v9[i] = v9[i] + gVu0.vf[19][i] * v8[3];
        }
        q = 1.0f / v9[3];
        v3[2] = gVu0.vf[13][2];
        src = src + 12;
        for (i = 0; i < 4; i++) {
            v8[i] = src[i];
        }
        for (i = 0; i < 3; i++) {
            v9[i] = v9[i] * q;
            v2[i] = v3[i] * q;
        }
        for (i = 0; i < 4; i++) {
            v3[i] = src[4 + i];
        }
        v10[0] = (s32)(v9[0] * 16.0f);
        v10[1] = (s32)(v9[1] * 16.0f);
        v10[2] = (s32)v9[2];
        v10[3] = (s32)v9[3];
        for (i = 0; i < 4; i++) {
            arg0[i] = v10[i];
            arg1[i] = v2[i];
        }
        arg0 = arg0 + 4;
        arg1 = arg1 + 4;
        count = count - 1;
    } while (count != 0);

    for (i = 0; i < 4; i++) {
        gVu0.vf[8][i] = v8[i];
        gVu0.vf[3][i] = v3[i];
        gVu0.vf[9][i] = v9[i];
        gVu0.vf[2][i] = v2[i];
        ((s32 *)gVu0.vf[10])[i] = v10[i];
    }
    gVu0.q = q;
}
