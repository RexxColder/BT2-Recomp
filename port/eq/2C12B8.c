#include "common.h"

void func_002C32B0(s32 arg0, s32 arg1, s32 arg2);
void func_002C32C8(s32 unused0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C12B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 var_s4;
    u8 *temp_s0;

    temp_s0 = (u8 *)arg0 + 0xD30;
    var_s4 = 0;
    func_002C32B0((s32)sp, arg1, arg2);
    temp_a3 = *(s32 *)(temp_s0 + 0x1F4);
    temp_a2 = temp_a3 + 0x1F;
    temp_a1 = temp_a3 < 0;
    if ((temp_a3 - *(s32 *)(temp_s0 + 0x1F8)) < 0x20) {
        *(s32 *)(temp_s0 + 0x1EC) = arg2;
        var_s4 = 1;
        *(s32 *)((u8 *)arg0 + (temp_a3 - ((((temp_a1 != 0) ? temp_a2 : temp_a3) >> 5) << 5)) * 4 + 0xF2C) = arg1;
        *(s32 *)(temp_s0 + 0x1F4) = *(s32 *)(temp_s0 + 0x1F4) + 1;
    }
    /* a0 is left by func_002C32B0 (not set again): dummy first argument */
    func_002C32C8(0, temp_a1, temp_a2, temp_a3);
    return var_s4;
}
