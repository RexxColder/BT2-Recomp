#include "common.h"

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0778(void);

s32 func_002DFE68(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_v0;

    var_v0 = func_002DCFE8(arg0, arg1, 0x40);
    temp_s0 = var_v0;
    if (temp_s0 != 0) {
        var_v0 = func_002E0778();
        temp_s0_2 = temp_s0 + 4;
        if (var_v0 != 0) {
            return 1;
        }
        temp_s1 = arg1 - (temp_s0_2 - arg0);
        if (temp_s1 > 0) {
            var_v0 = func_002DCFE8(temp_s0_2, temp_s1, -1);
            if (var_v0 != 0) {
                var_v0 = (func_002DCE50(var_v0) & 0x10) == 0;
            }
        }
        return var_v0;
    }
    return var_v0;
}
