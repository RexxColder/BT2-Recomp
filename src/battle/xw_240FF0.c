#include "common.h"

s32 func_00208768(s32 arg0, s32 arg1);

// Looks up the object at +0x1534 of arg0; returns 1 if there is none, else its halfword at +0x34.
s32  func_00240FF0(s32 arg0, s32 arg1) {
    s16 r;
    s32 obj;
    obj = func_00208768(*(s32 *)((u8 *)arg0 + 0x1534), arg1);
    __asm__ volatile("" : "+r"(obj));
    r = 1;
    if (obj != 0) {
        r = *(s16 *)(obj + 0x34);
    }
    return (s16)(r);
}
