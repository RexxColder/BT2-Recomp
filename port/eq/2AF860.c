#include "common.h"

extern f32 D_00387480;
extern f32 D_00387484;
extern f32 D_00387488;
extern f32 D_0038748C;
extern f32 D_00387490;
extern f32 D_00387494;
extern f32 D_00387498;
extern f32 D_0038749C;
extern f32 D_003874A0;
extern f32 D_003874A4;
extern f32 D_003874A8;
extern f32 D_003874AC;

void func_002AF860(s32 arg0, s32 arg1) {
    f32 t;
    f32 f1;
    f32 f2;
    f32 thr;

    if (arg1 == 0) {
        t = *(f32 *)(arg0 + 0x70) + (*(f32 *)(arg0 + 0x94) * D_00387480);
        if (t < D_00387484) {
            *(f32 *)(arg0 + 0x70) = t + D_00387488;
        }
        thr = D_0038748C;
    } else {
        f2 = *(f32 *)(arg0 + 0x70);
        f1 = *(f32 *)(arg0 + 0x15C) - f2;
        if (f1 < D_00387490) {
            f1 += D_00387494;
        }
        if (D_00387498 < f1) {
            f1 -= D_0038749C;
        }
        t = f2 + (f1 * D_003874A0);
        if (t < D_00387490) {
            *(f32 *)(arg0 + 0x70) = t + D_003874A4;
        }
        thr = D_00387498;
    }
    if (thr < *(f32 *)(arg0 + 0x70)) {
        *(f32 *)(arg0 + 0x70) = *(f32 *)(arg0 + 0x70) - D_003874A8;
    }
    *(f32 *)(arg0 + 0x74) = *(f32 *)(arg0 + 0x74) + (*(f32 *)(arg0 + 0x98) * D_003874AC);
}
