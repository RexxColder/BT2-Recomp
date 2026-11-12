#include "common.h"

void func_002C16E8(s32 arg0);
s32 func_002C1748(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C1750(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C1CB8(s32 arg0, s32 arg1, s32 arg2);
void func_002C1F58(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C2150(s32 arg0, s32 arg1, s32 arg2);

void func_002C1638(s32 arg0, s32 arg1, s32 arg2) {
    func_002C16E8(arg2);
    if (func_002C1748(arg0, arg1, arg2) != 0) {
        return;
    }
    if (func_002C1750(arg0, arg1, arg2) != 0) {
        return;
    }
    if (func_002C2150(arg0, arg1, arg2) != 0) {
        return;
    }
    if (func_002C1CB8(arg0, arg1, arg2) != 0) {
        return;
    }
    func_002C1F58(arg0, arg1, arg2);
}
