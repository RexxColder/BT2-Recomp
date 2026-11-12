#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D13D0(s32 arg0, s32 arg1, s32 arg2);

void func_002D1358(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002C3210(arg0, arg1, arg2) != 0) {
        func_002C2FF0(0, 0xFF000121, arg2);
        return;
    }
    func_002D13D0(arg0, arg1, arg2);
}
