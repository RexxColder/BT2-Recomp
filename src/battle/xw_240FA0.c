#include "common.h"

s32 func_00208768(s32 arg0, s32 arg1);

// Looks up the object at +0x1534 of arg0 through func_00208768 and returns its word at +8 (0 if none found).
s32 func_00240FA0(s32 arg0, s32 arg1) {
    s32 r;
    s32 obj;
    r = func_00208768(*(s32 *)((u8 *)arg0 + 0x1534), arg1);
    obj = r;
    __asm__ volatile("" : "+r"(obj));
    if (obj != 0) {
        r = *(s32 *)(obj + 8);
    }
    return r;
}
