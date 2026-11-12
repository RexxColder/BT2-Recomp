#include "common.h"

s32 func_002C4270(void *arg0, s32 arg1);
s32 func_002C4590(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
s32 func_002CC3D8(void *arg0, void *arg1, s32 arg2);
void func_002CC448(void *arg0, s32 arg1);
void func_002CC788(void *arg0, void *arg1, s32 arg2);
s32 func_002D07B0(void *arg0, s32 arg1);

s32 func_002C4098(void *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    u8 *s7;
    u8 *s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_v0;
    s32 do_block;
    u8 temp_v1;

    s7 = (u8 *)arg0 + 0x1F74;
    if (func_002D07B0(arg0, 5) == 0) {
        return 1;
    }
    s0 = *(u8 **)(s7 + 8);
    if (*(s32 *)(s0 + 0x34) == -1) {
        *(s32 *)(s0 + 0x34) = func_002C4270(arg0, arg1);
    }
    if (*(s32 *)(s0 + 0x2C) == -1) {
        *(s32 *)(s0 + 0x2C) = arg1;
    }
    temp_v0 = func_002D07B0(arg0, 0x1D);
    if (temp_v0 == -1) {
        var_a0 = *(s32 *)(s0 + 0x34);
    } else {
        var_a0 = *(s32 *)(s0 + 0x34);
        if (func_002D07B0(arg0, 0x37) == 0) {
            do_block = (arg1 == *(s32 *)(s0 + 0x2C));
        } else {
            do_block = (arg1 < *(s32 *)(s0 + 0x24));
        }
        if (do_block) {
            temp_v1 = arg2[3];
            if ((var_a0 != temp_v0) && (arg3 >= 4) && (*(s8 *)(arg2 + 0) == 0) && (*(s8 *)(arg2 + 1) == 0) && (arg2[2] == 1) && ((temp_v1 == 0xB3) || (temp_v1 == 0xB8))) {
                *(s32 *)(s0 + 0x34) = temp_v0;
                var_a0 = temp_v0;
            }
        }
    }
    *(s32 *)(s0 + 0x24) = arg1;
    var_v0 = 1;
    if (var_a0 == arg1) {
        temp_v0_2 = func_002CC3D8(arg0, arg2, arg3);
        var_v0 = 0;
        if (temp_v0_2 > 0) {
            temp_v0_3 = func_002C4590(arg0, *(s32 *)(s7 + 0x14), arg2, temp_v0_2, arg4);
            if (temp_v0_3 != 1) {
                func_002CC448(arg0, temp_v0_2);
            } else {
                func_002CC788(arg0, arg2, temp_v0_2);
            }
            var_v0 = temp_v0_3;
        }
    }
    return var_v0;
}
