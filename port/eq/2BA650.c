#include "common.h"

s32 func_002B9408(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D6F48(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002BA650(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 r = func_002B9408(arg0, arg1, arg2, arg3);

    func_002D6F48(r, arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF);
}
