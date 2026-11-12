#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D3030(s32 arg0, s32 arg1);
s32 func_002D3060(s32 arg0, s32 arg1);

s32 func_002CD1F8(s32 arg0) {
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;

    var_s2 = 1;
    if (func_002D07B0(arg0, 5) != 0) {
        var_s2 = func_002D3030(arg0, 6);
        var_s2 |= func_002D3060(arg0, 6);
    }
    var_s1 = 1;
    if (func_002D07B0(arg0, 6) != 0) {
        var_s1 = func_002D3030(arg0, 7);
        var_s1 |= func_002D3060(arg0, 7);
    }
    var_v0 = 0;
    if (var_s2 != 0) {
        var_v0 = 1;
        if (var_s1 == 0) {
            var_v0 = 0;
        }
    }
    return var_v0;
}
