#include "common.h"

s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_001F9D78(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* Calls func_001F9FB0(arg0, arg2); when it returns nonzero, calls func_001F9D78(arg0, arg1) and func_002113C0(arg0, 2, 1, 0).
   Returns the low byte of the first result. */
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = func_001F9FB0(arg0, arg2);

    if (r != 0) {
        func_001F9D78(arg0, arg1);
        func_002113C0(arg0, 2, 1, 0);
    }
    return r & 0xFF;
}
