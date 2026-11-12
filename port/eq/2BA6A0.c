#include "common.h"

s32 func_002B9408(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D6F88(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002BA6A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 r = func_002B9408(arg0, arg1, arg2, arg3);

    func_002D6F88(r, arg1, arg2, arg3);
}
