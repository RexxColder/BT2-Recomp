#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);
void func_002D03C8(s32 arg0, s32 arg1);

s32 func_002D0138(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    s32 temp_v1;

    var_v0 = func_002C3210(arg0, arg1, arg2);
    if (var_v0 != 0) {
        return func_002C2FF0(0, 0xFF00015A);
    }
    temp_v1 = *(s32 *) (arg0 + 0x36B0);
    if (temp_v1 != 0) {
        *(s32 *) (temp_v1 + 0xDCC) = arg2;
        *(s32 *) (temp_v1 + 0xDC8) = arg1;
        func_002D03C8(arg0, 0xFF00015A);
        var_v0 = 0;
    }
    return var_v0;
}
