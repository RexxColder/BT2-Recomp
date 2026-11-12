#include "common.h"

s32 func_00202DA0(s32 arg0, s32 arg1);

s32 func_00202DD8(s32 arg0, s32 arg1) {
    s32 var_a1;
    s32 var_s0;

    var_s0 = 0;
    if (*(s32 *) (arg0 + 0x1184) > 0) {
        var_a1 = 0;
        while (1) {
            if (*(s32 *) func_00202DA0(arg0, var_a1) != arg1) {
                var_s0 += 1;
                var_a1 = var_s0;
                if (var_s0 >= *(s32 *) (arg0 + 0x1184)) {
                    return 0;
                }
            } else {
                return func_00202DA0(arg0, var_s0);
            }
        }
    }
    return 0;
}
