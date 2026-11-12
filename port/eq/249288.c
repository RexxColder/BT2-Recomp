#include "common.h"

s32 func_00249288(s32 arg0, s32 arg1, void *arg2) {
    s32 var_a3;
    s32 var_t0;

    var_t0 = -1;
    if (arg1 > 0) {
        if (*(s32 *)arg2 != arg0) {
            var_a3 = 1;
            while (var_a3 < arg1 && *(s32 *)((u8 *)arg2 + var_a3 * 0x2C) != arg0) {
                var_a3 += 1;
            }
            if (var_a3 < arg1) {
                var_t0 = var_a3;
            }
        } else {
            var_t0 = 0;
        }
    }
    return var_t0;
}
