#include "common.h"
#include "vu0_state.h"

void func_001286B8(f32 arg0);

/* 0x001289D8 Mtx_RotateZ(dst, src, angle): func_001286B8 sets vf12 from the angle; vf8 = (vf12.y, vf12.x, 0, 0),
 * vf9 = (-vf12.x, vf12.y, 0, 0); each source row r (vf4..vf7, 16 bytes) becomes
 * ((vf8 * r.x + vf9 * r.y) + vf13 * r.z) + vf0 * r.w; the four rows go to dst. */
void Mtx_RotateZ(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 a8[4];
    f32 a9[4];
    f32 out[4][4];
    s32 i;
    s32 c;

    func_001286B8(arg2);
    a8[0] = gVu0.vf[12][1];
    a8[1] = gVu0.vf[12][0];
    a8[2] = 0.0f;
    a8[3] = 0.0f;
    a9[0] = 0.0f - gVu0.vf[12][0];
    a9[1] = gVu0.vf[12][1];
    a9[2] = 0.0f;
    a9[3] = 0.0f;
    for (i = 0; i < 4; i++) {
        f32 x = arg1[4 * i + 0];
        f32 y = arg1[4 * i + 1];
        f32 z = arg1[4 * i + 2];
        f32 w = arg1[4 * i + 3];

        for (c = 0; c < 4; c++) {
            f32 acc = a8[c] * x;
            acc = acc + a9[c] * y;
            acc = acc + gVu0.vf[13][c] * z;
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
