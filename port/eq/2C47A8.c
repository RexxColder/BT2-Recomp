#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1);

s32 func_002C47A8(s32 arg0) {
    u8 *t;
    s32 s2;
    s32 f;
    s32 v;

    s2 = 1;
    t = (u8 *)(arg0 + 0x1F74);
    f = *(s32 *)(t + 0x18);
    if (f != 8) {
        s2 = func_002C0EA8(arg0, f) & 1;
    }
    f = *(s32 *)(t + 0x14);
    if (f != 8) {
        s2 &= func_002C0EA8(arg0, f);
    }
    f = *(s32 *)(t + 0x1C);
    v = s2;
    if (f != 8) {
        v = s2 & func_002C0EA8(arg0, f);
    }
    return v;
}
