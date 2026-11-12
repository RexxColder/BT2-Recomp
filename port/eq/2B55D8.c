#include "common.h"

void func_002B55D8(u8 *arg0, u8 *arg1) {
    u8 *t = arg0 + 0x88;

    *(s32 *)(arg0 + 0x88) = *(s32 *)(arg1 + 0x58);
    *(s32 *)(t + 4) = *(s32 *)(arg1 + 0x5C);
    *(s32 *)(t + 8) = *(s8 *)(arg1 + 0x6C);
    *(s32 *)(t + 0xC) = *(s8 *)(arg1 + 0x6D);
    *(s32 *)(t + 0x14) = *(s32 *)(arg1 + 0x3C);
    *(s32 *)(t + 0x10) = *(s8 *)(arg1 + 0x6E);
    *(s32 *)(t + 0x1C) = 0;
    *(s32 *)(t + 0x18) = *(s32 *)(arg1 + 0x40);
}
