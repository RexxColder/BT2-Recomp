#include "common.h"

f32 sqrtf(f32 arg0);
f32 cosf(f32 arg0);

void func_002E9400(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3) {
    f32 f0, f1, f12, f20, f21, f22, t;

    f22 = 2.0f;
    f20 = sqrtf(f22);
    f21 = f20;
    f12 = (f32)arg0 * 6.2831855f;
    f12 = f12 / (f32)arg1;
    f0 = cosf(f12);
    f21 = f21 - f0;

    f1 = f20;
    if (f1 != f1) {
        f1 = sqrtf(f22);
    }
    f20 = f1 - 1.0f;

    f0 = f21 - f20;
    f12 = (f21 + f20) * f0;
    f0 = sqrtf(f12);
    f0 = f21 - f0;

    t = f0 / f20;
    f1 = -t;
    f1 = f1 * t;
    f1 = f1 * 4096.0f;
    f0 = (t + t) * 4096.0f;

    *arg2 = (s16)(s32)f0;
    *arg3 = (s16)(s32)f1;
}
