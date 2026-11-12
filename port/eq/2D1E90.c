#include "common.h"

void func_002D1E90(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_t1;
    u32 x;

    temp_t1 = *(s32 *)(arg1 + 0xC);
    x = (u32)(*(s32 *)(arg1 + 0x10) * 0xF) + (u32)(temp_t1 / 10);
    x = x * 2u;
    x += (u32)*(s32 *)(arg1 + 8) * 0x1A574u + (u32)temp_t1 * 0x706u;
    x += (u32)*(s32 *)(arg1 + 0x14) + (u32)*(s32 *)(arg1 + 0x18);
    x = x * 0x3E8u + (u32)((s32)*(s16 *)(arg1 + 0x1E) * 0x1F4);
    *arg2 = (s32)x;
    *arg3 = arg0;
}
