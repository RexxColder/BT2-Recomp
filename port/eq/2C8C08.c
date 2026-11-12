#include "common.h"

void func_002C8D80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D0E48(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D0EE8(s32 arg0, s32 arg1);
void func_002D1510(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D2748(s32 arg0);
s32 func_002DA360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C8C08(u8 *arg0, s32 arg1) {
    s32 sp[4];
    s32 (*temp_v0)(s32, s32, s32, s32);
    s32 temp_s3;
    s32 var_s4;
    s32 var_v0;
    u8 *temp_a2;
    u8 *temp_s1;
    u8 *temp_s5;

    temp_s1 = arg0 + 0xD30;
    var_s4 = 0;
    temp_a2 = arg0 + 0xDF0;
    temp_s5 = *(u8 **)(arg0 + 0x1FC0);
    if (*(s32 *)(arg0 + 0xE48) != 0) {
        var_s4 = (*(s32 *)(temp_a2 + 0x24) - *(s32 *)(arg0 + 0xE48 + 0x24)) + *(s32 *)(temp_s1 + 0x164);
    }
    temp_v0 = *(s32 (**)(s32, s32, s32, s32))(temp_s1 + 0x18);
    temp_s3 = *(s32 *)(temp_a2 + 0x28);
    if (temp_v0 != NULL) {
        return temp_v0((s32)arg0, arg1, var_s4, temp_s3);
    }
    if (arg1 == 1) {
        func_002D0E48((s32)temp_s1, var_s4, (s32)temp_a2);
    }
    if ((u32)(arg1 - 1) < 2U) {
        var_s4 = func_002D0EE8((s32)temp_s1, var_s4);
    }
    if (func_002D2748((s32)arg0) < 0x3E9) {
        var_v0 = 0;
        if (*(s32 *)(temp_s5 + 0x84) < *(s32 *)(arg0 + 0xAA4)) {
            goto block_11;
        }
    } else {
block_11:
        func_002D1510((s32)arg0, (s32)sp, (s32)&sp[1]);
        var_v0 = 0;
        if (sp[0] >= 0) {
            func_002C8D80((s32)arg0, arg1, (s32)&sp[2], (s32)&sp[3]);
            var_v0 = 0;
            if (func_002DA360(sp[0], sp[1], var_s4 - ((temp_s3 * sp[2]) / sp[3]), temp_s3) == 0) {
                var_v0 = 1;
                *(s32 *)(temp_s5 + 0x84) = *(s32 *)(temp_s5 + 0x84) + 1;
            }
        }
    }
    return var_v0;
}
