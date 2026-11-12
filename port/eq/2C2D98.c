#include "common.h"

s32 func_002C2D98(s32 arg0) {
    s32 r = -1;

    if (*(s32 *)(arg0 + 0x78) != 0) {
        if (*(s32 *)(arg0 + 0xD4 + 0x14) != 0) {
            r = *(s32 *)(arg0 + 0xD4 + 0x18);
        }
    }
    return r;
}
