#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1);
void func_002D3048(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D3060(s32 arg0, s32 arg1);
s32 func_002D4188(s32 arg0);

void func_002D4108(s32 arg0) {
    if (func_002D3060(arg0, 6) != 1 && func_002C0EA8(arg0, *(s32 *)(arg0 + 0x20D8)) == 1 && func_002D4188(arg0) != 0) {
        func_002D3048(arg0, 6, 1);
    }
}
