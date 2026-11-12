#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* Calls func_002113C0 with arg0, 2, 0x10, 1, then stores arg1 at +0x8E4 of arg0. */
void func_001F9D78(s32 arg0, s32 arg1) {
    func_002113C0(arg0, 2, 0x10, 1);
    *(s32 *)(arg0 + 0x8E4) = arg1;
}
