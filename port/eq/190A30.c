#include "common.h"

extern s32 D_003877BC;

s32 func_00190A30(u8 *arg0, s8 arg1) {
    s32 v = 0;

    if (D_003877BC != 0 && arg0 != NULL) {
        u8 *t = *(u8 **)(arg0 + 0x38);

        if (t != NULL && (*(u16 *)(t + 0x44) & 2)) {
            *(s8 *)(t + 0x58) = arg1;
            v = 1;
        }
    }
    return v;
}
