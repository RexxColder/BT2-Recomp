#include "common.h"

s32 func_002C0E40(s32 arg0, s32 arg1);
void func_002D3018(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D3030(s32 arg0, s32 arg1);
s32 func_002D4250(s32 arg0);

void func_002D41D0(s32 arg0) {
    if (func_002D3030(arg0, 6) != 1 && func_002C0E40(arg0, *(s32 *)(arg0 + 0x20D8)) == 1 && func_002D4250(arg0) != 0) {
        func_002D3018(arg0, 6, 1);
    }
}
