#include "common.h"

s32 func_002C0250(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C37D8(u8 *arg0, s32 arg1) {
    s32 r = func_002C0250((s32)arg0, *(s32 *)(arg0 + 0x1F84), arg1);

    if (r == 0) {
        *(s32 *)(arg0 + 0x37A8) = *(s32 *)(arg0 + 0x37A8) + arg1;
    }
    return r;
}
