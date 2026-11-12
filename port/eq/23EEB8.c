#include "common.h"

s32 Battle_GetSetup(s32 arg0);

s32  func_0023EEB8(s32 arg0) {
    s8 temp_v0_2;
    s8 var_v1;
    u8 *temp_v0;

    temp_v0 = (u8 *)(s32)Battle_GetSetup(arg0);
    temp_v0_2 = *(s8 *)(temp_v0 + 0x22);
    var_v1 = temp_v0_2;
    if (temp_v0_2 == 0) {
        var_v1 = *(s8 *)(temp_v0 + 0x20);
    }
    return (s8)(var_v1);
}
