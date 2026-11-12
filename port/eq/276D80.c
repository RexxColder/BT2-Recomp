#include "common.h"

s32 func_00276D00(s32 arg0);
s32 func_00276D40(s32 arg0);

s32 func_00276D80(s32 arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (func_00276D00(arg0) == 0) {
        var_v0 = func_00276D40(arg0) != 0;
    }
    return var_v0;
}
