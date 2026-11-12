#include "common.h"

extern s32 D_00387930;
s32 func_00211270(void);
s32 func_0020A658(s32 idx);
u8 *func_00211288(s32 idx);
void func_00312650(u8 *out, u8 *a, u8 *b);
f32 func_0029DFD0(u8 *v);
void func_001FBE80(f32 farg0, f32 farg1, u8 *ch);

/* 0x0020D048: for each character within `far` of pos, applies a distance falloff (1 at near, 0 at far) to (f24, f23). */
void func_0020D048(u8 *pos, f32 near, f32 far, f32 scaleA, f32 scaleB) {
    s32 i;
    u8 *ch;
    f32 d;
    f32 t;
    u8 sp[16];

    if (D_00387930 == 0) {
        return;
    }
    for (i = 0; i < func_00211270(); i++) {
        if (func_0020A658(i) != 0) {
            continue;
        }
        ch = func_00211288(i);
        func_00312650(sp, ch + 0x180, pos);
        d = func_0029DFD0(sp);
        if (d < far) {
            t = 1.0f - (d - near) / (far - near);
            if (1.0f < t) {
                t = 1.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            }
            func_001FBE80(scaleA * t, scaleB * t, ch);
        }
    }
}
