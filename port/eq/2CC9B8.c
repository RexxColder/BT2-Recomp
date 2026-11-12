#include "common.h"

s32 func_002CBE18(void *arg0);

s32 func_002CC9B8(void *arg0) {
    s32 var_v0;
    u8 *temp_a0;

    if (func_002CBE18(arg0) == 0) {
        return 1;
    }
    temp_a0 = *(u8 **)((u8 *)arg0 + 0x1FC0) + 0x1128;
    var_v0 = 1;
    if (*(s32 *)(temp_a0 + 0x20) != 1) {
        var_v0 = (*(s32 *)(temp_a0 + 0xC) < 3) == 0;
    }
    return var_v0;
}
