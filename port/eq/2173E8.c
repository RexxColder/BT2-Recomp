#include "common.h"

f32 func_00210A48(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00385AF0;

f32 func_002173E8(f32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    f32 result;
    f32 t14;
    f32 t13;
    f32 f1;

    result = arg0;
    if (func_00211310(arg1, 0, 1) != 0) {
        t13 = arg2 * func_00210A48(arg1);
        t14 = arg0 * arg3;
        f1 = 1.0f;
        if (t13 < t14 && D_00385AF0 < t14) {
            f1 = t13 / t14;
        }
        result = arg0 * f1;
    }
    return result;
}
