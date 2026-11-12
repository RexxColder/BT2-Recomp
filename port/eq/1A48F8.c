#include "common.h"

s32 func_001A48F8(u8 *arg0) {
    s32 var_v0;
    u8 *temp_a0;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a0 = *(u8 **)(arg0 + 0x38);
        if (temp_a0 != NULL) {
            var_v0 = (*(s32 *)(temp_a0 + 0x50) & 1) != 0;
        }
    }
    return var_v0;
}
