#include "common.h"

s32 func_0023FFD8(s32 arg0, s32 arg1);

s32  func_002407D8(s32 arg0, s32 arg1) {
    s8 temp_v0_2;
    s8 var_v1;
    u8 *temp_v0;

    temp_v0 = (u8 *)func_0023FFD8(arg0, arg1);
    temp_v0_2 = *(s8 *)(temp_v0 + 0x25);
    var_v1 = temp_v0_2;
    if (temp_v0_2 == 0) {
        var_v1 = *(s8 *)(temp_v0 + 0x24);
    }
    return (s8)(var_v1);
}
