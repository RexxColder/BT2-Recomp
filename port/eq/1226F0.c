#include "common.h"

void func_001226F0(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xFE0;

    *(s32 *)(p + 0x2C) = arg1;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x30) = 0;
}
