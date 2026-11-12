#include "common.h"

f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(s32 arg0);
s32 func_00203CC0(s32 arg0);
extern f32 D_00383E48;
extern f32 D_00383E4C;
extern f32 D_00383E50;
extern f32 D_00383E54;

void func_0010F3F0(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    u8 *s1;
    f32 f;
    s32 r;

    r = *(s32 *)func_00203CC0(arg1);
    if (r >= 0x2710) {
        f = *(f32 *)(p + 0x24);
        if (f == 0.0f) {
            return;
        }
        s1 = p + 0x14;
        if (Ramp_Step((s32)s1) == 0) {
            return;
        }
        f = *(f32 *)(p + 0x24);
        if (f == 1.0f) {
            Ramp_Start((s32)s1, 0.5f, 1.0f, 0.0f);
            return;
        }
        Ramp_Start((s32)s1, 0.5f, D_00383E54, 1.0f);
        return;
    }
    s1 = p + 0x14;
    if (*(f32 *)(p + 0x24) == 0.0f) {
        Ramp_Start((s32)s1, 0.5f, D_00383E48, 1.0f);
    }
    if (Ramp_Step((s32)s1) != 0) {
        if (*(f32 *)(p + 0x24) != 1.0f) {
            Ramp_Start((s32)s1, 0.5f, D_00383E4C, 1.0f);
            return;
        }
        Ramp_Start((s32)s1, 0.5f, 1.0f, D_00383E50);
    }
}
