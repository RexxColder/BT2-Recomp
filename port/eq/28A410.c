#include "m2c_macros.h"

s32 McCard_IsFatalError(s32 arg0) {
    s32 var_v0 = 1;

    if ((u32)(arg0 + 0x13) >= 9U && (u32)(arg0 + 0x31) >= 0xAU && (u32)(arg0 + 0x3B) >= 0xAU) {
        var_v0 = (u32)(arg0 + 0x4F) < 0xAU;
    }
    return var_v0;
}
