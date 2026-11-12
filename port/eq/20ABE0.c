#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

s32 func_0020ABE0(u32 arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    if (D_00387930 != 0 && arg0 < 2U) {
        temp_v0 = func_00217488(func_00211288((s32)arg0));
        var_v0 = 1;
        if (temp_v0 != 0x8A) {
            if (temp_v0 >= 0x8B) {
                var_v1 = 0x8C;
            } else {
                var_v1 = 0x88;
            }
            if (temp_v0 != var_v1) {
                var_v0 = 0;
            }
        }
    }
    return var_v0;
}
