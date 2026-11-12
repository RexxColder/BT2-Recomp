#include "common.h"

f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 sinf(f32 farg0);
f32 func_0029DFD0(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
extern u8 *D_003876A0;
extern s32 gBtlCamView;
extern f32 D_00385A4C;

void func_00212C40(s32 arg0, s32 *arg1, s32 *arg2) {
    u8 sp[0x60];
    f32 f20;
    f32 f21;
    f32 ang;
    f32 t;
    s32 s0;
    s32 v;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        *arg1 = 0x7F;
        *arg2 = 0x40;
        return;
    }
    sceVu0InversMatrix((s32)(sp + 0x20), gBtlCamView);
    func_00312650((s32)sp, arg0, (s32)(sp + 0x50));
    f20 = func_0029DFD0((s32)sp);
    func_003126C8((s32)(sp + 0x10), (s32)(sp + 0x40));
    f21 = atan2f(*(f32 *)(sp + 0), *(f32 *)(sp + 8));
    ang = BtlUtil_WrapAngle(f21 - atan2f(*(f32 *)(sp + 0x10), *(f32 *)(sp + 0x18)));

    /* first output: cvt.w.s (truncates toward zero) of (1 - (f20 - 200) / D) * 127, clamped */
    f20 = (f20 - 200.0f) / D_00385A4C;
    t = (1.0f - f20) * 127.0f;
    v = (s32)t;
    s0 = v;
    if (s0 < 0) {
        s0 = 0;
    }
    if (s0 >= 0x80) {
        s0 = 0x7F;
    }
    t = sinf(ang);
    *arg1 = s0;

    /* second output: cvt.w.s (truncates toward zero) of sin * 64 + 64, clamped */
    t = (t * 64.0f) + 64.0f;
    v = (s32)t;
    if (v < 0) {
        v = 0;
    }
    if (v >= 0x80) {
        v = 0x7F;
    }
    *arg2 = v;
}
