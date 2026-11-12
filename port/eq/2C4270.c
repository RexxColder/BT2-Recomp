#include "common.h"

void func_002C4DB8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D07B0(s32 arg0, s32 arg1);

s32 func_002C4270(s32 arg0, s32 arg1) {
    s32 sp[2];
    s32 temp_v0;

    temp_v0 = func_002D07B0(arg0, 0x3B);
    if (temp_v0 != 2) {
        return arg1;
    }
    func_002C4DB8(arg0, (s32) sp, (s32) &sp[1]);
    if (sp[1] < 2) {
        return arg1;
    }
    return temp_v0;
}
