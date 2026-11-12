#include "common.h"

void func_001FC880(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

void func_00230BB0(s32 arg0, s32 arg1) {
    s32 sel;

    if (func_00211310(arg0, 7, 0x20000) == 0) {
        sel = (arg1 == 3) ? 1 : 0;
        func_001FC880(arg0, sel);
    }
}
