#include "common.h"

void BtlOpp_GetDelta(s32 arg0, s32 arg1);
f32 BtlOpp_GetHalfHeightDiff(s32 arg0);
f32 Mathf_Asin(f32 arg0);
f32 func_0029DFD0(s32 arg0);
s32 func_00312680(s32 arg0, s32 arg1, f32 farg0);
extern f32 D_00385A18;

f32 BtlOpp_GetPitchAdjusted(s32 arg0) {
    f32 sp[4];
    f32 h;
    f32 t;
    f32 v;

    BtlOpp_GetDelta(arg0, (s32)sp);
    h = BtlOpp_GetHalfHeightDiff(arg0);
    sp[1] = sp[1] + h;
    t = func_0029DFD0((s32)sp);
    v = 0.0f;
    if (D_00385A18 < t) {
        func_00312680((s32)sp, (s32)sp, 1.0f / t);
        v = -Mathf_Asin(sp[1]);
    }
    return v;
}
