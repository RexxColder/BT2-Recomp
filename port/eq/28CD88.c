#include "common.h"

s32 func_0028CB60(void);
s32 dpadd(s32 arg0, s64 arg1);
s32 dpmul(s32 arg0, s64 arg1);
s32 litodp(s32 arg0);

s32 func_0028CD88(void) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_0028CB60();
    var_v0 = litodp(temp_v0);
    if (temp_v0 < 0) {
        var_v0 = dpadd(var_v0, (s64)0x83E0 << 47);
    }
    return dpmul(var_v0, (s64)0xF7C0 << 46);
}
