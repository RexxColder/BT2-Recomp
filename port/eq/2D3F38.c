#include "common.h"

void func_002C00A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D3FB0(s32 arg0);

void func_002D3F38(s32 arg0, s32 *arg1, s32 arg2) {
    s32 s0 = (s32)arg1 + 4;
    s32 s1 = 0;
    s32 a2;
    s32 a3;

    *arg1 = 0;
    do {
        func_002D3FB0(s0);
        a2 = s1;
        s1 += 1;
        a3 = s0;
        s0 += 0x10;
        func_002C00A8(arg0, arg2, a2, a3);
    } while (s1 < 3);
}
