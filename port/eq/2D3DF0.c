#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1);
void func_002D3048(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D3060(s32 arg0, s32 arg1);
s32 func_002D3E70(s32 arg0);

void func_002D3DF0(s32 arg0) {
    if (func_002D3060(arg0, 8) != 1 && func_002C0EA8(arg0, *(s32 *)(arg0 + 0x2160)) == 1 && func_002D3E70(arg0) != 0) {
        func_002D3048(arg0, 8, 1);
    }
}
