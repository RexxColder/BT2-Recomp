#include "common.h"
#include "vu0_state.h"

void func_001286B8(f32 arg0);

/* 0x00129230 Vu0Cur_RotateX(angle in f12): vf8 = (0, c, s, 0), vf9 = (0, -s, c, 0) (s = vf12.x, c = vf12.y); each
 * current row r (vf16..vf19) becomes ((vf15 * r.x + vf8 * r.y) + vf9 * r.z) + vf0 * r.w. */
void Vu0Cur_RotateX(f32 arg0) {
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
    a[0] = 0.0f;  a[1] = c;  a[2] = s;  a[3] = 0.0f;
    b[0] = 0.0f;  b[1] = 0.0f - s;  b[2] = c;  b[3] = 0.0f;
    for (i = 0; i < 4; i++) {
        gVu0.vf[8][i] = a[i];
        gVu0.vf[9][i] = b[i];
    }
    for (r = 0; r < 4; r++) {
        for (i = 0; i < 4; i++) {
            row[i] = gVu0.vf[16 + r][i];
        }
        for (i = 0; i < 4; i++) {
            f32 acc = gVu0.vf[15][i] * row[0];
            acc = acc + a[i] * row[1];
            acc = acc + b[i] * row[2];
            gVu0.vf[16 + r][i] = acc + gVu0.vf[0][i] * row[3];
        }
    }
}
