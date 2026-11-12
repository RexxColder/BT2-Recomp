#include "common.h"

s32 func_0028CB60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s64 litodp(s32 arg0);
s64 dpadd(s64 arg0, s64 arg1);
s64 dpmul(s64 arg0, s64 arg1);

void func_0028CD28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp;
    s64 v;

    temp = func_0028CB60(arg0, arg1, arg2, arg3);
    v = litodp(temp);
    if (temp < 0) {
        v = dpadd(v, (s64)0x83E0 << 47);
    }
    dpmul(v, ((s64)0x3DF00000 << 32) | 0x100000);
}
