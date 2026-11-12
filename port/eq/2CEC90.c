#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002CEC90(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000135, 0xA, arg1, arg2);
        return;
    }
    func_002D2FC8(arg0, 0, 0xA, arg1, arg2);
}
