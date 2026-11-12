#include "common.h"

s32 func_0024AD60(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a0;
    s32 var_t3;

    temp_a3 = *(s32 *) arg1;
    var_t3 = 1;
    var_a0 = temp_a3 - 1;
    for (;;) {
        temp_v1 = (var_a0 >= 0) ? var_a0 : 6;
        *(s32 *) arg1 = temp_v1;
        if (temp_a3 == temp_v1) {
            var_t3 = 0;
            break;
        }
        if ((u32) (*(s32 *) (arg0 + 0x2C * (arg2 * 7 + temp_v1)) - 0x83) < 3U) {
            var_a0 = temp_v1 - 1;
            continue;
        }
        break;
    }
    return var_t3;
}
