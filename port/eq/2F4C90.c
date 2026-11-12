#include "common.h"

s32 func_002F4960(s32 arg0, s32 arg1, s32 arg2);

s32 func_002F4C90(s32 arg0) {
    s32 sp[2];
    f32 x;
    f32 frac;
    s32 t;

    func_002F4960(arg0, (s32)&sp[0], (s32)&sp[1]);
    x = ((f32)sp[0] / (f32)sp[1]) * 100.0f;
    t = (s32)x;
    frac = x - (f32)t;
    if ((frac > 0.5f) || ((frac == 0.5f) && ((t & 1) != 0))) {
        t += 1;
    } else if ((frac < -0.5f) || ((frac == -0.5f) && ((t & 1) != 0))) {
        t -= 1;
    }
    return t;
}
