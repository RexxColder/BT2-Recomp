#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);

typedef s32 (*VFunc1)(s32);

s32 func_002BF478(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *obj;

    /* a1 is not written before the first call: passed through */
    if (func_002C3210((s32)arg0, arg1) != 0) {
        func_002C2FF0(0, 0xFF0001A4);
        return 0;
    }
    var_v0 = func_002D07B0((s32)arg0, 6);
    if (var_v0 != 0) {
        obj = *(u8 **)(arg0 + 0x2114);
        var_v0 = ((VFunc1)(*(s32 *)(obj + 0x10)))((s32)arg0);
    }
    return var_v0;
}
