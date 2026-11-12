#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void *BtlChar_GetPos(s32 arg0);
f32 func_00217330(s32 arg0);
extern f32 D_00385AE8;
extern f32 D_00385AEC;

f32 func_00217360(s32 arg0) {
    f32 temp_f0;
    f32 temp_f20;
    f32 var_f0;

    var_f0 = 0.0f;
    if (func_00211310(arg0, 0, 4) == 0) {
        temp_f20 = *(f32 *) ((s32) BtlChar_GetPos(arg0) + 0x54);
        var_f0 = D_00385AEC;
        if (!(temp_f20 < D_00385AE8)) {
            temp_f0 = func_00217330(arg0);
            var_f0 = 0.0f;
            if (!(temp_f0 < 0.0f)) {
                var_f0 = temp_f0 / temp_f20;
            }
        }
    }
    return var_f0;
}
