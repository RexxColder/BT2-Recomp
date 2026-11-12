#include "common.h"

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DFB20(s32 *arg0, s32 *arg1, s32 *arg2) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    temp_v0 = func_002DCFE8(*arg0, *arg1, -1);
    var_v0 = 0;
    if (temp_v0 == 0) {
        var_a1 = *arg1;
    } else {
        var_v0 = func_002DCE50(temp_v0);
        var_a1 = temp_v0 - *arg0;
    }
    *arg1 -= var_a1;
    *arg0 += var_a1;
    *arg2 += var_a1;
    return var_v0;
}
