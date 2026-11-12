#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023F410(s32 arg0);
extern s32 D_00387930 __attribute__((section(".data")));

s32 func_0020AA78(u32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        temp_v0 = func_00211288((s32) arg0);
        if (func_0023F410(temp_v0) & 0x800) {
            var_v0 = 1;
            if (func_00211310(temp_v0, 1, 0x1000) != 0) {
                var_v0 = 1;
                if (func_00211310(temp_v0, 1, 0x2000) == 0) {
                    var_v0 = 0;
                }
            }
        } else {
            var_v0 = 1;
            if (func_00211310(temp_v0, 1, 0x2000) == 0) {
                var_v0 = 0;
            }
        }
    } else {
        var_v0 = 0;
    }
    return var_v0;
}
