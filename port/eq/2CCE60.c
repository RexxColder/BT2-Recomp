#include "common.h"

s32 func_002CCE60(s32 arg0) {
    s32 r = 1;

    if ((u32)(*(s32 *)(arg0 + 0x48) - 1) < 4U) {
        r = (*(s32 *)(arg0 + 0x44) == 0);
    }
    return r;
}
