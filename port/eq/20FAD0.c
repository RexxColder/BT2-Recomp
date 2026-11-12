#include "common.h"

extern void *D_003876A0;
extern s32 gBtlCamView;

void sceVu0InversMatrix(void *arg0, s32 arg1);
void func_00312650(void *arg0, s32 arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
void func_003126C8(void *arg0, void *arg1);
f32 atan2f(f32 arg0, f32 arg1);
f32 BtlUtil_WrapAngle(f32 arg0);
f32 sinf(f32 arg0);

void func_0020FAD0(s32 arg0, f32 farg0, f32 farg1, s32 *arg1, s32 *arg2) {
    f32 buf[24];
    f32 f20, f21, t, u, angle, sv;
    s32 k, s0, r;

    if ((*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 2) != 0) {
        *arg1 = 0x7F;
        *arg2 = 0x40;
        return;
    }
    sceVu0InversMatrix(buf + 8, gBtlCamView);
    func_00312650(buf, arg0, buf + 20);
    f20 = func_0029DFD0(buf);
    func_003126C8(buf + 4, buf + 16);
    f20 = f20 - farg0;
    f21 = atan2f(buf[0], buf[2]);
    angle = BtlUtil_WrapAngle(f21 - atan2f(buf[4], buf[6]));
    t = (1.0f - f20 / (farg1 - farg0)) * 127.0f;
    k = (s32)t;
    if (t - (f32)k > 0.5f || (t - (f32)k == 0.5f && (k & 1))) {
        k++;
    } else if (t - (f32)k < -0.5f || (t - (f32)k == -0.5f && (k & 1))) {
        k--;
    }
    s0 = k;
    if (s0 < 0) {
        s0 = 0;
    }
    if (s0 >= 0x80) {
        s0 = 0x7F;
    }
    sv = sinf(angle);
    *arg1 = s0;
    u = sv * 64.0f + 64.0f;
    k = (s32)u;
    if (u - (f32)k > 0.5f || (u - (f32)k == 0.5f && (k & 1))) {
        k++;
    } else if (u - (f32)k < -0.5f || (u - (f32)k == -0.5f && (k & 1))) {
        k--;
    }
    r = k;
    if (r < 0) {
        r = 0;
    }
    if (r >= 0x80) {
        r = 0x7F;
    }
    *arg2 = r;
}
