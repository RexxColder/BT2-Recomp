#include "common.h"

extern u8 *D_003878F4;

void func_001E8B08(void) {
    u8 *p;

    p = D_003878F4 + 0x218;
    *(s32 *)(p + 0x82C) = 0;
    *(s32 *)(p + 0x8C) = 0;
    *(s32 *)(p + 0x2CC) = 0;
}
