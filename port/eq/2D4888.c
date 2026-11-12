#include "common.h"

s32 func_002D4888(u8 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 26; i++) {
        u8 *e = arg0 + 0x180 + 64 * i;

        if (e[0x18] == arg1) {
            return (s32)e;
        }
    }
    return 0;
}
