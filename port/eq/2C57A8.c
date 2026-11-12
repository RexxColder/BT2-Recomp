#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E05A8(s32 arg0, s32 arg1, s32 arg2);

void func_002C57A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;

    var_v1 = 0;
    if (arg0 != 0) {
        if (func_002C3210(arg0, arg1, arg2) != 0) {
            func_002C2FF0(0, 0xFF000181);
            return;
        }
        var_v1 = *(s32 *)(*(s32 *)((u8 *)arg0 + 0x1FC0));
    }
    if (func_002E05A8(var_v1, arg1, ((arg1 ^ 5) != 0) ? arg2 : 0) != 0) {
        func_002C2FF0(arg0, 0xFF000F12);
    }
}
