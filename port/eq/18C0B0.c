#include "common.h"

extern s32 D_003877B4;

s32 func_0018C0B0(u8 *arg0, s8 arg1) {
    s32 v = 0;

    if (D_003877B4 != 0 && arg0 != NULL) {
        u8 *t = *(u8 **)(arg0 + 0x38);

        if (t != NULL && (*(s32 *)(t + 0x1D8) & 2)) {
            *(s8 *)(t + 0x1DC) = arg1;
            v = 1;
        }
    }
    return v;
}
