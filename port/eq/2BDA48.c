#include "common.h"

void func_002C12B8(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002F4CE0(s32 arg0, s32 arg1);
s32 func_002F4D68(s32 arg0);

void func_002BDA48(u8 *arg0) {
    u8 *t;
    s32 a1;
    s32 s1;
    s32 s2;
    s32 v;

    t = arg0 + 0xD30;
    a1 = *(s32 *)(t + 0x1F8);
    s1 = **(s32 **)(arg0 + 0x2004);
    if (*(s32 *)(t + 0x1F4) != a1) {
        return;
    }
    s2 = func_002F4CE0(s1, a1);
    v = func_002F4D68(s1);
    if (s2 > 0 && v > 0) {
        func_002C12B8(arg0, s2, v);
    }
}
