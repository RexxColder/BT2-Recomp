#include "common.h"

s32 func_002D4440(s32 arg0, s32 arg1);
s32 func_002D4658(s32 arg0, s32 arg1);
void func_002D4508(s32 arg0);

s32 func_002C2428(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 var_v0;

    var_v0 = func_002D4440(arg0, arg1);
    if (var_v0 == 0) {
        return 0;
    }
    if (func_002D4658(var_v0, (s32)sp) == 0) {
        sp[0] = 0;
    }
    func_002D4508(var_v0);
    return sp[0];
}
