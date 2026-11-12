#include "common.h"

s32 func_002C66E0(u8 *arg0, u32 arg1) {
    u32 base;
    u32 b2;
    s32 ret;

    base = *(u32 *)(arg0 + 0);
    ret = (s32)(arg1 - base);
    if (arg1 < base || arg1 >= (u32)(base + *(s32 *)(arg0 + 4))) {
        b2 = *(u32 *)(arg0 + 8);
        ret = 0;
        if (arg1 >= b2 && arg1 < (u32)(b2 + *(s32 *)(arg0 + 0xC))) {
            ret = (s32)(arg1 - b2) + *(s32 *)(arg0 + 4);
        }
    }
    return ret;
}
