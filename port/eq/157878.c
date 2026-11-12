#include "common.h"

void *func_00157878(s32 arg0) {
    s32 var_v1;
    u8 *var_a0;
    void *var_a1;

    var_a0 = (u8 *)arg0 + 0xF40;
    var_a1 = NULL;
    var_v1 = 1;
    do {
        var_v1 -= 1;
        if (*(s32 *)(var_a0 + 4) == 0) {
            var_a1 = var_a0;
        }
        var_a0 += 8;
    } while (var_v1 >= 0);
    return var_a1;
}
