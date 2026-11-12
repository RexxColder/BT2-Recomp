#include "common.h"

u32 strlen(s8 *arg0);

s32 func_002FECA8(s8 *arg0) {
    u32 n = strlen(arg0);
    u32 a2 = (n >= 0x11U) ? 0x10U : n;
    u32 k;

    if (a2 == 0) {
        return 0;
    }
    for (k = 0; k < a2; k++) {
        if (arg0[k] == 0x3A) {
            return 1;
        }
    }
    return 0;
}
