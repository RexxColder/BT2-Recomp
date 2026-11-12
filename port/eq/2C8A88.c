#include "common.h"

s32 func_002DA360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C8A88(s32 arg0) {
    s32 temp_a2;
    s32 var_v0;
    s32 temp_a1;
    s32 temp_t0;

    temp_a1 = arg0 + 0x36B4;
    var_v0 = 0;
    temp_a2 = *(s32 *)(temp_a1 + 4);
    temp_t0 = arg0 + 0xDF0;
    if ((temp_a2 >= 0) && (*(s32 *)(arg0 + 0xE48) == 0)) {
        var_v0 = func_002DA360(temp_a2, *(s32 *)(temp_a1 + 8), *(s32 *)(temp_t0 + 0x24), *(s32 *)(temp_t0 + 0x28)) == 0;
    }
    return var_v0;
}
