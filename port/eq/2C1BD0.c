#include "common.h"

s32 func_002DC538(s32 arg0);

s32 func_002C1BD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = arg1;
    var_s0 = arg0;
    if (var_s1 >= 4) {
loop_1:
        var_s1 -= 1;
        if (func_002DC538(var_s0) == arg2) {
            return var_s0;
        }
        var_s0 += 1;
        if (var_s1 < 4) {
            return 0;
        }
        goto loop_1;
    }
    return 0;
}
