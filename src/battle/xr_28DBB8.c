#include "m2c_macros.h"

/* Col_NearEq: returns 1 when |a - b| <= eps (eps is the third argument, in $f14). */
s32 Col_NearEq(f32 arg0, f32 arg1, f32 arg2) {
    s32 var_v0;

    var_v0 = 1;
    if (!(fabsf(arg0 - arg1) <= arg2)) {
        var_v0 = 0;
    }
    return var_v0;
}
