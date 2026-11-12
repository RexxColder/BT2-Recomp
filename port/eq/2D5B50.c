#include "common.h"

extern void func_002D7080(u8 *arg0, s32 arg1, s32 arg2);

/* 0x002D5B50: stores arg4 at +0x44 and arg5 at +0x48 of arg1, then tail-calls func_002D7080(arg1, arg2, arg3). */
void func_002D5B50(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    *(s32 *)(arg1 + 0x44) = arg4;
    *(s32 *)(arg1 + 0x48) = arg5;
    func_002D7080(arg1, arg2, arg3);
}
