#include "common.h"

s32 func_002BC170(s32 arg0);

s32 func_002BC1A0(u8 *arg0) {
    s32 v;

    v = func_002BC170(*(s32 *)(arg0 + 4));
    if (v != 0) {
        v = 0;
        if (*(s32 *)(arg0 + 0) == 1) {
            v = *(s32 *)(arg0 + 0x1C) != 0;
        }
    }
    return v;
}
