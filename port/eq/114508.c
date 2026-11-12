#include "common.h"

void func_00114468(s32 arg0, s32 arg1, s32 arg2);

void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;

    var_s2 = arg2 & 0xFF;
    var_s3 = arg1;
    if (arg3 > 0) {
        var_s1 = arg0;
        var_s0 = arg3;
        var_a0 = var_s1;
        do {
            var_s1 += 0x60;
            var_s0 -= 1;
            func_00114468(var_a0, var_s3, var_s2);
            var_a0 = var_s1;
        } while (var_s0 != 0);
    }
}
