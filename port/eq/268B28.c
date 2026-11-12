#include "common.h"

s32 func_00268B28(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_v0;

    var_a3 = 0;
    var_a2 = 8;
    do {
        var_a2_2 = var_a2 + 0xE;
        var_a1 = 0;
        var_a3 += 1;
        do {
            var_a1 += 1;
            temp_v0 = var_a3 < arg0;
            var_a2_2 += 0x24;
            if (temp_v0 == 0) {
                break;
            }
            if (var_a1 >= 0x12) {
                break;
            }
            var_a3 += 1;
        } while (1);
        var_a2 = var_a2_2 + 1;
    } while (temp_v0 != 0);
    temp_v1 = var_a2 - (((var_a2 < 0 ? var_a2 + 3 : var_a2) >> 2) * 4);
    if (temp_v1 != 0) {
        var_v0 = 4 - temp_v1;
        if (var_v0 > 0) {
            do {
                var_v0 -= 1;
                var_a2 += 1;
            } while (var_v0 != 0);
        }
    }
    return var_a2 + 4;
}
