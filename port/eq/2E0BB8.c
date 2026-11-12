#include "common.h"

s64 __divdi3(s64 arg0, s64 arg1);
s64 __muldi3(s64 arg0, s64 arg1);

u64 func_002E0BB8(s64 arg0, s64 arg1, s64 arg2) {
    s64 var_a0;
    s64 var_a1;
    s64 var_s0;
    s32 var_s1;
    s64 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_s0 = arg2;
    if (var_s0 == 0) {
        return ((var_a0 ^ var_a1) < 0) ? ((u64)0x8000 << 48) : (((u64)-1) >> 1);
    }
    var_s1 = 1;
    if (var_a0 < 0) {
        var_s1 = -1;
        var_a0 = 0 - var_a0;
    }
    if (var_a1 < 0) {
        var_s1 = -var_s1;
        var_a1 = 0 - var_a1;
    }
    if (var_s0 < 0) {
        var_s0 = 0 - var_s0;
        var_s1 = -var_s1;
    }
    temp_v0 = __divdi3(__muldi3(var_a0, var_a1) + ((s64)(var_s0 + ((u64)var_s0 >> 0x3F)) >> 1), var_s0);
    return (var_s1 < 0) ? (u64)(0 - temp_v0) : (u64)temp_v0;
}
