#include "common.h"

s32 Gsc_GetCurrentTime(s32 arg0);
f32 Gsc_GetFloat(void);

s32 func_002A7BB0(s32 arg0) {
    s32 var_s0;
    s32 temp_t;
    f32 temp_f;
    f32 x;
    s32 r;

    var_s0 = 0;
    if (arg0 == 2) {
        temp_t = Gsc_GetCurrentTime(arg0);
        temp_f = Gsc_GetFloat();
        x = temp_f * 300.0f;
        /* cvt.w.s truncates toward zero (saturating): plain cast */
        r = (s32)x;
        var_s0 = temp_t >= r;
    }
    return var_s0;
}
