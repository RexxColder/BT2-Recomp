#include "common.h"

s32 func_002C1BD0(s32 arg0, s32 arg1, s32 arg2);
void func_002C18F0(s32 arg0, s32 arg1, s32 *arg2);

s32 func_002C1808(s32 arg0, s32 arg1, s32 *arg2) {
    s32 *var_s6;
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_v0;

    var_s6 = arg2;
    var_s3 = arg0;
    var_s4 = arg1;
    *var_s6 = 0;
    var_v0 = func_002C1BD0(arg0, arg1, 0x10000);
    var_s1 = var_v0;
    var_s2 = var_s1 - var_s3;
    var_s5 = var_s4 - var_s2;
    if (var_s1 != 0) {
        var_v0 = func_002C1BD0(var_s1 + 1, var_s5 - 1, 0x10000);
        var_s0 = var_v0;
        if (var_s0 != 0) {
            var_v0 = func_002C1BD0(var_s0 + 1, (var_s4 - (var_s0 - var_s3)) - 1, 0x10000);
            temp_a0 = var_v0 - var_s0;
            if (var_v0 != 0) {
                var_s0 -= var_s1;
                var_v0 = -1;
                if ((var_s0 == temp_a0) && ((var_s2 % var_s0) == 0)) {
                    func_002C18F0(var_s1, var_s5, var_s6);
                    var_v0 = var_s0;
                }
            }
        }
    }
    return var_v0;
}
