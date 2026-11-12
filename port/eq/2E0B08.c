#include "common.h"

s64 __divdi3(s64 arg0, s64 arg1);
s64 __muldi3(s64 arg0, s64 arg1);

s64 func_002E0B08(s32 arg0, s32 arg1, s32 arg2) {
    s64 var_a0;
    s64 var_a1;
    s64 var_s0;
    s64 var_s1;
    s64 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    if (arg2 == 0) {
        return ((var_a0 ^ var_a1) < 0) ? -0x80000000LL : 0x7FFFFFFFLL;
    }
    var_s0 = arg2;
    var_s1 = 1;
    if (var_a0 < 0) {
        var_s1 = -1;
        var_a0 = -var_a0;
    }
    if (var_a1 < 0) {
        var_s1 = -var_s1;
        var_a1 = -var_a1;
    }
    if (var_s0 < 0) {
        var_s0 = -var_s0;
        var_s1 = -var_s1;
    }
    temp_v0 = __muldi3(var_a0, var_a1);
    temp_v0 = __divdi3(temp_v0 + ((var_s0 + ((u64)var_s0 >> 63)) >> 1), var_s0);
    if (var_s1 < 0) {
        temp_v0 = -temp_v0;
    }
    return (s64)(s32)temp_v0;
}
