#include "common.h"

s32 func_002B5AD0(u8 *arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 var_a0;

    temp_a1 = *(s32 *)(arg0 + 0x80);
    temp_v0 = *(s32 *)(arg0 + 0x7C);
    var_a0 = temp_a1 + 1;
    if (temp_a1 >= temp_v0) {
        var_a0 = ((temp_v0 ^ temp_a1) == 0) ? temp_a1 : 0;
    }
    return var_a0;
}
