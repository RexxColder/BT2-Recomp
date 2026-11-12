#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D14F8(s32 arg0, s32 arg1, s32 arg2);

void func_002D1480(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002C3210(arg0, arg1, arg2) != 0) {
        func_002C2FF0(0, 0xFF000127, arg2);
        return;
    }
    func_002D14F8(arg0, arg1, arg2);
}
