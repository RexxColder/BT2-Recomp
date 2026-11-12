#include "common.h"
#include "vu0_state.h"

void func_001286B8(f32 arg0);

/* 0x001291C0 Vu0Cur_RotateZ(angle in f12): func_001286B8 leaves sin in vf12.x and cos in vf12.y. vf8 = (c, s, 0, 0),
 * vf9 = (-s, c, 0, 0); each current row r (vf16..vf19) becomes ((vf8 * r.x + vf9 * r.y) + vf13 * r.z) + vf0 * r.w. */
void Vu0Cur_RotateZ(f32 arg0) {
    f32 a[4];
    f32 b[4];
    f32 row[4];
    s32 r;
    s32 i;
    f32 s;
    f32 c;

    func_001286B8(arg0);
    s = gVu0.vf[12][0];
    c = gVu0.vf[12][1];
    a[0] = c;  a[1] = s;  a[2] = 0.0f;  a[3] = 0.0f;
    b[0] = 0.0f - s;  b[1] = c;  b[2] = 0.0f;  b[3] = 0.0f;
    for (i = 0; i < 4; i++) {
        gVu0.vf[8][i] = a[i];
        gVu0.vf[9][i] = b[i];
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            row[i] = gVu0.vf[16 + r][i];
        }
        for (i = 0; i < 4; i++) {
            f32 acc = a[i] * row[0];
            acc = acc + b[i] * row[1];
            acc = acc + gVu0.vf[13][i] * row[2];
            gVu0.vf[16 + r][i] = acc + gVu0.vf[0][i] * row[3];
        }
    }
}
