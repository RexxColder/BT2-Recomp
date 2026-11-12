#include "common.h"

s32 func_0025FBE8(void *arg0, s64 arg1) {
    s64 var_a2;
    u8 *var_a0;
    s64 temp_v0;
    s32 var_v1;

    var_v1 = *(s8 *)((u8 *)arg0 + 0xD7E);
    var_a2 = 0;
    if (var_v1 > 0) {
        var_a0 = (u8 *)arg0 + 0xD88;
        do {
            temp_v0 = *(s64 *)var_a0;
            var_a0 += 8;
            var_v1 -= 1;
            var_a2 |= temp_v0 & arg1;
        } while (var_v1 != 0);
    }
    return var_a2 != 0;
}
