#include "common.h"

extern s32 D_003877B0;

s32 func_00187D80(u8 *arg0, s8 arg1) {
    s32 v = 0;

    if (D_003877B0 != 0 && arg0 != NULL) {
        u8 *t = *(u8 **)(arg0 + 0x38);

        if (t != NULL && (*(s32 *)(t + 0x19C) & 2)) {
            *(s8 *)(t + 0x1A0) = arg1;
            v = 1;
        }
    }
    return v;
}
