#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1);
void func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002CEC20(s32 arg0, s32 arg1) {
    if (func_002C3210(arg0, arg1) != 0) {
        func_002C2FF0(0, 0xFF000134, 9, arg1, 0);
        return;
    }
    func_002D2FC8(arg0, 0, 9, arg1, 0);
}
