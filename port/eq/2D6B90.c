#include "common.h"

void *memset(void *s, s32 c, u32 n);

void func_002D6B90(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    memset(arg0, 0, 0x94);
    temp_v1 = (arg1 + 0x1F) & ~0x1F;
    *(s32 *)(arg0 + 0x50) = arg1;
    *(s32 *)(arg0 + 0x54) = arg2;
    *(s32 *)(arg0 + 0) = 1;
    *(s32 *)(arg0 + 0x3C) = temp_v1 + 0x400;
    *(s32 *)(arg0 + 0x40) = temp_v1 + 0x800;
    *(s32 *)(arg0 + 0x44) = temp_v1 + 0xC00;
    *(s32 *)(arg0 + 0x58) = -1;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(s32 *)(arg0 + 0x28) = 1;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x38) = temp_v1;
    *(s32 *)(arg0 + 0x64) = 0;
}
