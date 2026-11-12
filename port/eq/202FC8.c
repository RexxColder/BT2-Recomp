#include "common.h"

s32 *func_00202DA0(u8 *arg0, s32 arg1);

s32 func_00202FC8(u8 *arg0, s32 arg1) {
    s32 i = 0;

    if (*(s32 *)(arg0 + 0x1184) <= 0) {
        return -1;
    }
    do {
        s32 k = i;

        i += 1;
        if (*func_00202DA0(arg0, k) == arg1) {
            return k;
        }
    } while (i < *(s32 *)(arg0 + 0x1184));
    return -1;
}
