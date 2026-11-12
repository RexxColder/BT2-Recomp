#include "common.h"

extern u8 *D_00387A40 __attribute__((section(".data")));

s32 func_002A9980(s32 arg0) {
    s32 var_v0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)(D_00387A40 + 8) + arg0 * 0x1520;
    var_v0 = 0;
    if (*(s32 *)(temp_v1 + 0xC) != 0) {
        var_v0 = (*(s32 *)(temp_v1 + 0xAF0) & 2) != 0;
    }
    return var_v0;
}
