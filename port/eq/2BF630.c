#include "common.h"

s32 func_002D3060(s32 arg0, s32 arg1);
s32 func_002C0EA8(s32 arg0, s32 arg1);
void func_002D3048(s32 arg0, s32 arg1, s32 arg2);

void func_002BF630(u8 *arg0) {
    if ((func_002D3060((s32)arg0, 7) != 1) && (func_002C0EA8((s32)arg0, *(s32 *)(arg0 + 0x211C)) == 1)) {
        func_002D3048((s32)arg0, 7, 1);
    }
}
