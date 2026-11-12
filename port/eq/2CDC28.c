#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D3060(s32 arg0, s32 arg1);

s32 func_002CDC28(s32 arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a0;
    u8 *temp_v1;

    temp_v1 = (u8 *)arg0 + 0xA0C;
    if (*(s32 *)(temp_v1 + 0x18) == 0) {
        if (*(s32 *)(temp_v1 + 0x14) == 0) {
            return 1;
        }
    }
    temp_s2 = func_002D3060(arg0, 6);
    temp_s1 = func_002D3060(arg0, 7);
    temp_v0 = func_002D07B0(arg0, 0x19);
    switch (temp_v0) {
    case 0:
        var_a0 = temp_s1 & temp_s2;
        break;
    case 1:
        var_a0 = temp_s1;
        break;
    case 2:
        var_a0 = temp_s2;
        break;
    case 3:
        var_a0 = temp_s1 | temp_s2;
        break;
    default:
        return 0;
    }
    return var_a0;
}
