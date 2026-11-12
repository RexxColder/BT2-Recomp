#include "common.h"

s32 func_002B9408(s32 arg0);
void func_002D6F30(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);

void func_002BA5E0(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 x0;
    s32 x1;
    s32 x2;

    func_002D6F30(func_002B9408(arg0), &x0, &x1, &x2);
    *arg1 = x0;
    *arg3 = ((x2 ^ 1) != 0) ? 0 : x2;
    *arg2 = x1;
}
