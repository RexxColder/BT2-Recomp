#include "common.h"

void BtlOpp_GetDelta(s32 arg0, s32 arg1);
f32 func_0029DFD0(s32 arg0);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
f32 Mathf_Asin(f32 farg0);
extern f32 D_00385A14;

f32 BtlOpp_GetPitch(s32 arg0) {
    s32 sp[4];
    f32 temp_f0;
    f32 var_f2;

    BtlOpp_GetDelta(arg0, (s32)sp);
    temp_f0 = func_0029DFD0((s32)sp);
    var_f2 = 0.0f;
    if (D_00385A14 < temp_f0) {
        func_00312680((s32)sp, (s32)sp, 1.0f / temp_f0);
        var_f2 = -Mathf_Asin(((f32 *)sp)[1]);
    }
    return var_f2;
}
