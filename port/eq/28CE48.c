#include "common.h"

s32 func_0028CB60(s32 arg0);
s64 litodp(s32 arg0);
s64 dpadd(s64 arg0, s64 arg1);
s64 dpmul(s64 arg0, s64 arg1);

s64 func_0028CE48(s32 arg0) {
    u32 var_s0;
    u32 var_s1;
    s64 var_v0;
    s64 var_v0_2;
    s64 var_s0_d;

    var_s0 = (u32)func_0028CB60(arg0) >> 5;
    var_s1 = (u32)func_0028CB60(0) >> 6;
    var_v0 = litodp((s32)var_s0);
    if ((s32)var_s0 < 0) {
        var_v0 = dpadd(var_v0, (s64)0x83E0 << 47);
    }
    var_s0_d = dpmul(var_v0, (s64)0x8320 << 47);
    var_v0_2 = litodp((s32)var_s1);
    if ((s32)var_s1 < 0) {
        var_v0_2 = dpadd(var_v0_2, (s64)0x83E0 << 47);
    }
    return dpmul(dpadd(var_s0_d, var_v0_2), (s64)0xF280 << 46);
}
