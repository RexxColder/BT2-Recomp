#include "common.h"

s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002C8920(u8 *arg0, s32 arg1);
void func_002C8980(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_002C8A88(u8 *arg0);
s32 func_002C8AD8(u8 *arg0, s32 arg1);
s32 func_002C8B28(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002C8C08(u8 *arg0, s32 arg1);

s32 func_002C8828(u8 *arg0, s32 arg1) {
    s32 temp_s1_2;
    s32 var_s3;
    s32 var_v0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s1 = *(u8 **)(arg0 + 0x1FC0);
    var_v0 = func_002D07B0(arg0, 0x2F);
    temp_s2 = temp_s1 + 0x8C;
    if (var_v0 != 1) {
        if (func_002D07B0(arg0, 0x27) != 1) {
            if (*(s8 *)(temp_s2 + 0x58) != 0) {
                return *(s32 *)(temp_s1 + 0x16C);
            }
            temp_s1_2 = *(s32 *)(temp_s2 + 0x18);
            var_s3 = 1;
            if (func_002C8A88(arg0) == 0) {
                if ((func_002C8AD8(arg0, temp_s1_2) == 0) && (func_002C8B28(arg0, temp_s1_2, arg1) == 0)) {
                    if (func_002C8920(arg0, temp_s1_2) == 0) {
                        var_s3 = func_002C8C08(arg0, temp_s1_2) != 0;
                    }
                }
            }
            func_002C8980(arg0, temp_s2, var_s3);
            var_v0 = var_s3;
            return var_v0;
        }
        return 0;
    }
    return var_v0;
}
