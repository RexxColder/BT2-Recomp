#include "common.h"

f32 atan2f(f32 farg0, f32 farg1);
f32 sinf(f32 farg0);
f32 func_0029DFD0(f32 *arg0);
void func_00312650(f32 *arg0, s32 arg1, f32 *arg2);
void func_003126C8(f32 *arg0, f32 *arg1);
void sceVu0InversMatrix(f32 *arg0, s32 arg1);
extern f32 D_003872DC;
extern f32 D_003872E0;
extern f32 D_003872E4;
extern f32 D_003872E8;
extern f32 D_003872EC;
extern s32 gBtlCamView;

f32 func_002A8D90(s32 arg0, s32 *arg1, s32 *arg2) {
    f32 buf[32];
    f32 *sp10;
    f32 *m;
    f32 *sp50;
    f32 f0;
    f32 f12;
    f32 f20;
    f32 f21;
    f32 x;
    s32 s0;
    s32 t;

    /* the frame of the original: vec at +0, vec at +0x10, 4x4 matrix at +0x20 (overlapping +0x50) */
    sp10 = &buf[4];
    m = &buf[8];
    sp50 = &buf[20];
    sceVu0InversMatrix(m, gBtlCamView);
    func_003126C8(sp10, sp50);
    f21 = atan2f(buf[16], buf[18]);
    func_00312650(buf, arg0, sp10);
    f20 = func_0029DFD0(buf);
    f12 = atan2f(buf[0], buf[2]) - f21;
    f20 = (f20 - 200.0f) / D_003872E0;
    if (f12 < D_003872DC) {
        f12 += D_003872E4;
    }
    if (D_003872E8 < f12) {
        f12 -= D_003872EC;
    }

    /* cvt.w.s of (1 - f20) * 127 (truncates toward zero), then clamp to 0..127 */
    x = (1.0f - f20) * 127.0f;
    t = (s32)x;
    s0 = t;
    if (s0 < 0) {
        s0 = 0;
    }
    if (s0 >= 0x80) {
        s0 = 0x7F;
    }
    f0 = sinf(f12);
    *arg1 = s0;
    f0 = (f0 * 64.0f) + 64.0f;

    /* cvt.w.s of the return value, clamp to 0..127 */
    x = f0;
    t = (s32)x;
    if (t < 0) {
        t = 0;
    }
    if (t >= 0x80) {
        t = 0x7F;
    }
    *arg2 = t;
    return f0;
}
