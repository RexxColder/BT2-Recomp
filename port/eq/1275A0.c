#include "common.h"

s32 func_001275A0(u8 *arg0) {
    u8 *t;
    s32 a1;

    if (*(s32 *)(arg0 + 0xC) != 1) {
        return 1;
    }
    t = *(u8 **)(*(u8 **)(arg0 + 0x64) + 0x20);
    if (*(s32 *)(t + 0x4) != 0) {
        if ((*(s32 *)(t + 0x0) ^ 0xD9) == 0) {
            a1 = 0;
        } else {
            a1 = (*(s32 *)(t + 0x8) != 7);
        }
        return a1;
    }
    if (*(s32 *)(t + 0x8) == 4) {
        return 0;
    }
    return 1;
}
