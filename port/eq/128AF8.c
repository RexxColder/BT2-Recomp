#include "common.h"
#include "vu0_state.h"

void func_001286B8(f32 arg0);

/* 0x00128AF8 Mtx_RotateY(dst, src, angle): vf8 = (vf12.y, 0, -vf12.x, 0), vf9 = (vf12.x, 0, vf12.y, 0); each source
 * row becomes ((vf8 * r.x + vf14 * r.y) + vf9 * r.z) + vf0 * r.w; the four rows go to dst. */
void Mtx_RotateY(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 a8[4];
    f32 a9[4];
    f32 out[4][4];
    s32 i;
    s32 c;

    func_001286B8(arg2);
    a8[0] = gVu0.vf[12][1];
    a8[1] = 0.0f;
    a8[2] = 0.0f - gVu0.vf[12][0];
    a8[3] = 0.0f;
    a9[0] = gVu0.vf[12][0];
    a9[1] = 0.0f;
    a9[2] = gVu0.vf[12][1];
    a9[3] = 0.0f;
    for (i = 0; i < 4; i++) {
        f32 x = arg1[4 * i + 0];
        f32 y = arg1[4 * i + 1];
        f32 z = arg1[4 * i + 2];
        f32 w = arg1[4 * i + 3];

        for (c = 0; c < 4; c++) {
            f32 acc = a8[c] * x;
            acc = acc + gVu0.vf[14][c] * y;
            acc = acc + a9[c] * z;
            acc = acc + gVu0.vf[0][c] * w;
            out[i][c] = acc;
        }
    }
    for (i = 0; i < 4; i++) {
        for (c = 0; c < 4; c++) {
            arg0[4 * i + c] = out[i][c];
            gVu0.vf[4 + i][c] = out[i][c];
        }
    }
    for (c = 0; c < 4; c++) {
        gVu0.vf[8][c] = a8[c];
        gVu0.vf[9][c] = a9[c];
    }
}
