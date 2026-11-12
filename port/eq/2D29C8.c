#include "common.h"

void func_002D2A80(s32 arg0, s32 arg1);
s32 func_002D2AC8(s32 arg0, s32 arg1);
void func_002C2FF0(s32 arg0, s32 arg1);

void func_002D29C8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_s3;
    s32 *var_s1;
    s32 temp_a1;
    s32 var_s2;
    u8 *var_s0;
    u8 *temp_a0;

    temp_s3 = *arg2;
    var_s0 = (u8 *)arg1;
    var_s1 = (s32 *)temp_s3;
    var_s2 = 8;
    *(s32 *)(var_s0 + 8) = 0;
    for (;;) {
        temp_a0 = var_s0;
        var_s2 -= 1;
        var_s0 += 0x44;
        temp_a1 = *var_s1;
        var_s1 += 1;
        func_002D2A80((s32)temp_a0, temp_a1);
        if (var_s2 < 0) {
            break;
        }
        *(s32 *)(var_s0 + 8) = 0;
    }
    if (func_002D2AC8(arg0, temp_s3) != 0) {
        func_002C2FF0(arg0, 0xFF000302);
    }
}
