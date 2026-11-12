#include "common.h"

f32 BtlOpp_GetDistance(s32 arg0);
f32 BtlOpp_GetPitchAdjusted(s32 arg0);
s32 func_00126040(s32 arg0);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
f32 func_00210A98(s32 arg0);
extern f32 D_00384124;
extern f32 D_00384128;

s32 func_00124A00(s32 arg0) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f2;
    s32 temp_v0;
    s32 var_v0;

    if ((func_00126058(arg0, 0, 1) != 0) || (func_00126058(arg0, 0, 0x2000) != 0)) {
        var_v0 = 1;
    } else if (func_00126058(arg0, 0, 0x400) == 0) {
        temp_v0 = func_00126040(arg0);
        temp_f20 = func_00210A98(temp_v0);
        temp_f20 = fabsf(temp_f20);
        temp_f21 = BtlOpp_GetPitchAdjusted(temp_v0);
        temp_f2 = BtlOpp_GetDistance(temp_v0);
        var_v0 = 0;
        if (temp_f20 < D_00384124) {
            if (fabsf(temp_f21) < D_00384128) {
                var_v0 = (temp_f2 < 800.0f);
            }
        }
    } else {
        var_v0 = 0;
    }
    return var_v0;
}
