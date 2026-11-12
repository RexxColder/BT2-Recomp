#include "common.h"

s32 func_001E53C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a3;
    f32 ref;

    var_a3 = arg1 + 1;
    if (arg2 < var_a3) {
        return -1;
    }
    ref = *(f32 *) (arg0 + arg1 * 4);
    while (1) {
        if (*(f32 *) (arg0 + var_a3 * 4) != ref) {
            break;
        }
        var_a3 += 1;
        if (arg2 < var_a3) {
            return -1;
        }
    }
    if (*(f32 *) (arg0 + var_a3 * 4) <= ref) {
        return arg1;
    }
    return var_a3;
}
