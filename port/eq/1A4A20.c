#include "common.h"

s32 func_001A4A20(void *arg0, f32 farg0) {
    s32 var_v0;
    u8 *temp_a0;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
        if ((temp_a0 != NULL) && (*(s32 *)(temp_a0 + 0x50) & 1)) {
            *(f32 *)(temp_a0 + 0x14) = farg0;
            var_v0 = 1;
        }
    }
    return var_v0;
}
