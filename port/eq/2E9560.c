#include "common.h"

s32 func_002E9560(u16 *arg0, s32 arg1, s16 *arg2) {
    s32 temp_a1;
    s32 var_t0;
    s32 var_a3;

    temp_a1 = arg1 - 1;
    var_t0 = 0x7FFFFFFF;
    var_a3 = 0;
    if (temp_a1 > 0) {
        if (arg0[0] != 0x80) {
            var_a3 = 2;
            while (var_a3 < temp_a1) {
                if (*(u16 *) ((u8 *) arg0 + var_a3) == 0x80) {
                    if (var_a3 < var_t0) {
                        var_t0 = var_a3;
                    }
                    break;
                }
                var_a3 += 2;
            }
        } else {
            var_t0 = 0;
        }
    }
    if (var_t0 == 0x7FFFFFFF) {
        *arg2 = 0;
        return -1;
    }
    *arg2 = (s16) var_t0;
    return 0;
}
