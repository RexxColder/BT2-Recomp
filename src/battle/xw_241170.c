#include "common.h"

s32 func_00208768(s32 arg0, s32 arg1);

// Looks up the object at +0x1534 of arg0; returns 1 if its halfword at +0x4A is zero, else 0 (the call result when none).
s32 func_00241170(s32 arg0, s32 arg1) {
    s32 r;
    s32 obj;
    s32 test;
    obj = func_00208768(*(s32 *)((u8 *)arg0 + 0x1534), arg1);
    test = obj;
    __asm__ volatile("" : "+r"(test));
    r = obj;
    if (test != 0) {
        r = (*(s16 *)(test + 0x4A) == 0);
    }
    return r;
}
