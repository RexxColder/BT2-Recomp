#include "common.h"

extern u8 *D_00387850 __attribute__((section(".data")));

s32 func_001AE050(s32 arg0) {
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)(D_00387850 + arg0 * 4 + 0x5A8);
    var_v0 = 0;
    if (temp_v1 != NULL) {
        temp_a0 = *(u8 **)(temp_v1 + 0x38);
        var_v0 = 1;
        *(s32 *)(temp_a0 + 0x20) = *(s32 *)(temp_a0 + 0x20) | 1;
    }
    return var_v0;
}
