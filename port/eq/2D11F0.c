#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002D1118(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3);

s32 func_002D11F0(s32 arg0) {
    s32 sp[2];
    s32 var_v0;

    var_v0 = func_002D07B0(arg0, 6);
    if (var_v0 != 0) {
        var_v0 = func_002D07B0(arg0, 0x33);
        if (var_v0 != 0) {
            func_002D1118(arg0, arg0 + 0xD30, sp, sp + 1);
            var_v0 = var_v0 < (sp[0] / sp[1]);
        }
    }
    return var_v0;
}
