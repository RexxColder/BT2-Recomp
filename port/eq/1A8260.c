#include "common.h"

extern u8 *gEftStruggle;

void func_001A8260(void) {
    u8 *p;

    p = gEftStruggle + 0x10;
    *(s32 *)(p + 0x60C) = 0;
    *(s32 *)(p + 0x8C) = 0;
    *(s32 *)(p + 0x1AC) = 0;
    *(s32 *)(p + 0x4EC) = 0;
}
