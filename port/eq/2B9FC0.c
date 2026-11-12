#include "common.h"

s32 func_002B9FC0(s32 arg0) {
    s32 v1 = *(s32 *)(arg0 + 0x20);
    s32 r = 1;

    if (v1 != 0) {
        r = 0;
        if (v1 == 0x101) {
            r = 1;
        }
    }
    return r;
}
