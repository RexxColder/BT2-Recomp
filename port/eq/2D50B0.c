#include "common.h"

s32 func_002D50B0(u8 *arg0, s32 *arg1) {
    s32 var_v0 = 0;

    *arg1 = 0;
    if (*(s32 *)(arg0 + 0xC) >= 0xE1) {
        var_v0 = 1;
        *arg1 = *(s32 *)(*(u8 **)(arg0 + 4) + 0xB0 + 0x14);
    }
    return var_v0;
}
