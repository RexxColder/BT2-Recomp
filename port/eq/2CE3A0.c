#include "common.h"

s32 func_002D2838(s32 arg0);
s32 func_002DA708(s32 arg0, s32 arg1, s32 arg2);

void func_002CE3A0(s32 arg0) {
    s32 s0;
    s32 s2 = 4;

    func_002DA708(arg0, 0, 0x38);
    s0 = arg0;
    do {
        func_002D2838(s0);
        s0 += 0x20;
        s2 -= 1;
    } while (s2 >= 0);
    func_002D2838(arg0 + 0xA0);
    *(s64 *)(arg0 + 0xC0) = 0;
    *(s32 *)(arg0 + 0xDC) = 0;
    *(s64 *)(arg0 + 0xC8) = 0;
    *(s64 *)(arg0 + 0xD0) = 0;
    *(s32 *)(arg0 + 0xD8) = 0;
}
