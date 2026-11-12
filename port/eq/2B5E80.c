#include "common.h"

s32 func_002B5B60(s32 arg0);
s32 func_002B5CF8(s32 arg0);
s32 func_002B5FC8(s32 arg0);
s32 func_002D4440(s32 arg0, s32 arg1);
void func_002D4508();
s32 func_002D4658(s32 arg0, s32 *arg1);

void func_002B5E80(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 v0;
    s32 v1;
    s32 a1;
    s32 a2;
    u8 *t1;

    *(s32 *)(arg0 + 0xB4) = *(s32 *)(arg0 + 0xB4) + 1;
    if (arg2 < 0x800) {
        return;
    }
    if (arg1 == 0) {
        return;
    }
    s2 = func_002D4440(arg1, arg2);
    if (s2 == 0) {
        return;
    }
    v1 = func_002D4658(s2, sp);
    if (v1 != 1) {
        func_002D4508(s2);
        return;
    }
    s4 = sp[0];
    if (s4 != v1) {
        func_002D4508(s2);
        return;
    }

    s1 = func_002B5FC8(s2);
    s0 = func_002B5B60(s2);
    v0 = func_002B5CF8(s2);
    v1 = *(s32 *)(arg0 + 0xBC) * 0x14;
    t1 = arg0 + (v1 + 0xC0);
    *(s32 *)(t1 + 4) = *(s32 *)(arg0 + 0xB4) - 1;
    *(s32 *)(t1 + 8) = s1;
    *(s32 *)(t1 + 0xC) = s0;
    *(s32 *)(arg0 + v1 + 0xD0) = v0;
    *(s32 *)(t1 + 0) = s4;

    v1 = *(s32 *)(arg0 + 0xBC);
    a1 = v1 + 1;
    a2 = a1 < 0;
    a1 = a1 - (((a2 != 0) ? (v1 + 8) : a1) >> 3) * 8;
    *(s32 *)(arg0 + 0xBC) = a1;
    func_002D4508(s2, a1, a2, (s32)t1);
}
