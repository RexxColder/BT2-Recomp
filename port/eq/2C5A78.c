#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C5B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C5A78(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_002C3210(arg0, arg1, arg2, arg3) != 0) {
        func_002C2FF0(0, 0xFF000185, arg2, arg3);
        return;
    }
    func_002C5B00(arg0, arg1, arg2, arg3);
}
