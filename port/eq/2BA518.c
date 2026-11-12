#include "common.h"

s32 func_002B9408(s32 arg0);
s32 func_002B9430(s32 arg0, s32 arg1, s32 *arg2);
void func_002D6EF8(s32 arg0, s32 *arg1, s32 arg2, s32 arg3);

void func_002BA518(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[40];
    s32 s1;

    s1 = func_002B9408(arg0);
    func_002B9430(arg0, arg1, buf);
    func_002D6EF8(s1, buf, arg2, arg3);
}
