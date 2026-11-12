#include "common.h"

s32 func_002CAC18(s32 arg0, s32 arg1);

s32 func_002C5FC0(s32 arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_v0;

    var_s0 = *(s32 *)((u8 *)arg0 + 0xA68);
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2C);
    var_s0 = (~var_s0 == 0) ? temp_v0 : var_s0;
    temp_a1 = temp_v0 < var_s0;
    var_s0 = (temp_a1 != 0) ? temp_v0 : var_s0;
    temp_v0_2 = func_002CAC18(arg0, temp_a1);
    var_v0 = temp_v0_2 < var_s0;
    if (*(s32 *)((u8 *)arg0 + 0x58) == 2) {
        var_v0 = (temp_v0_2 + *(s32 *)((u8 *)arg0 + 0x968)) < var_s0;
    }
    return var_v0 == 0;
}
