#include "common.h"

s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002C2D98(u8 *arg0);
void func_002C57A8(u8 *arg0, s32 arg1, s32 arg2);

void func_002C5D88(u8 *arg0) {
    s32 r;

    if (func_002D07B0(arg0, 0x1C) == 0) {
        return;
    }
    r = func_002C2D98(arg0);
    if (r == 0) {
        func_002C57A8(arg0, 5, 1);
    } else if (r != -1) {
        func_002C57A8(arg0, 5, 0);
    }
}
