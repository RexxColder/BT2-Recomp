#include "common.h"

s32 func_00208768(s32 arg0, s32 arg1);

// Looks up the object at +0x1534 of arg0; returns 1 if there is none, else its signed byte at +0x36 plus 1.
s32 func_00241020(s32 arg0, s32 arg1) {
    s32 r;
    s32 obj;
    obj = func_00208768(*(s32 *)((u8 *)arg0 + 0x1534), arg1);
    __asm__ volatile("" : "+r"(obj));
    r = 1;
    if (obj != 0) {
        r = *(s8 *)(obj + 0x36) + 1;
    }
    return r;
}
