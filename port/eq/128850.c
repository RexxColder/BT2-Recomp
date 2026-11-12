#include "common.h"

/* 0x00128850 Mtx_TranslateLocal: arg0 rows 0..2 = arg1 rows 0..2; arg0 row 3 = arg1 row 0 * v.x + row 1 * v.y +
 * row 2 * v.z + row 3 * v.w (per component), with v = arg2 (VU0 vmulax / vmadday / vmaddaz / vmaddw). */
void Mtx_TranslateLocal(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 r[4][4];
    f32 row3[4];
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            r[j][i] = arg1[j * 4 + i];
        }
    }
    for (i = 0; i < 4; i++) {
        f32 acc = r[0][i] * arg2[0];

        acc = acc + r[1][i] * arg2[1];
        acc = acc + r[2][i] * arg2[2];
        row3[i] = acc + r[3][i] * arg2[3];
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            arg0[j * 4 + i] = r[j][i];
        }
    }
    for (i = 0; i < 4; i++) {
        arg0[12 + i] = row3[i];
    }
}
