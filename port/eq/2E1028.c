#include "common.h"

extern s32 (*D_00347B6C)(s32 arg0, s32 arg1, s32 arg2, s32 arg3) __attribute__((section(".data")));

s32 func_002E1028(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;

    var_v0 = 0;
    if (D_00347B6C != NULL) {
        var_v0 = D_00347B6C(arg0, arg1, arg2, arg3);
    }
    return var_v0;
}
