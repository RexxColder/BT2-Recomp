#include "common.h"

s32 func_002D10A8(s32 arg0, s32 arg1) {
    s32 r = 0;

    if (*(s32 *)(arg1 + 0x2CC) != -1) {
        r = (*(s32 *)(arg0 + 0x4C) == 4);
    }
    return r;
}
