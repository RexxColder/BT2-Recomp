#include "common.h"

void func_002D7058(u8 *arg0, s32 arg1) {
    s32 even = ((arg1 + (s32)((u32)arg1 >> 31)) >> 1) << 1;
    s32 half = even >> 1;

    *(s32 *)(arg0 + 0xC) = even;
    *(s32 *)(arg0 + 0x1C) = half;
    *(s32 *)(arg0 + 0x2C) = half;
}
