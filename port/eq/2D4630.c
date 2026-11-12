#include "common.h"

s32 func_002D4630(s32 *arg0) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = *arg0;
    var_v0 = 1;
    if (temp_v0 < 2) {
        var_v0 = 0;
        if (temp_v0 < -1) {
            var_v0 = 1;
        }
    }
    return var_v0;
}
