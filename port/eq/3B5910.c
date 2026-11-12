#include "common.h"

s32 func_003B5910(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;

    var_v0 = 1;
    if ((arg2 > 0) && (arg0 <= 0xFFEF) && (arg0 > 0)) {
        var_v0 = (arg1 <= 0xFFEF) ? (arg1 < 1) : 1;
    }
    return var_v0;
}
