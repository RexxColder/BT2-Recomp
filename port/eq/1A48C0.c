#include "common.h"

s32 func_001A48C0(u8 *arg0) {
    u8 *t;
    s32 v = 0;

    if (arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(s32 *)(t + 0x50) & 1)) {
            *(s32 *)(t + 0x50) = *(s32 *)(t + 0x50) | 4;
            v = 1;
        }
    }
    return v;
}
