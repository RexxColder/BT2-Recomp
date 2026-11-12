#include "common.h"

s32 func_00241ED0(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0x984) + ((arg1 != 0) * 4) + 0x60;
    var_v0 = *(s32 *)(temp_v1 + 8);
    if (var_v0 == 0) {
        var_v0 = *(s32 *)temp_v1;
    }
    return var_v0;
}
