#include "common.h"

void func_002E25B8(u8 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a2;
    s32 temp_v1;
    u32 temp_v0;
    u32 var_v0;

    temp_a0 = (*(s32 *)(arg0 + 0x50) << 12) | *(s32 *)(arg0 + 4);
    temp_a2 = (*(s32 *)(arg0 + 0x54) << 12) | *(s32 *)(arg0 + 8);
    *(u32 *)(arg0 + 0x2CC) = (u32)((u32)(temp_a0 + 0xF) >> 4);
    *(s32 *)(arg0 + 0x2C4) = temp_a0;
    *(s32 *)(arg0 + 0x2C8) = temp_a2;
    if (*(s32 *)(arg0 + 0x48) == 1) {
        *(u32 *)(arg0 + 0x2D0) = (u32)((u32)(temp_a2 + 0xF) >> 4);
    } else {
        temp_v0 = temp_a2 + 0x1F;
        if (*(s32 *)(arg0 + 0x118) == 3) {
            var_v0 = (temp_v0 >> 5) * 2;
        } else {
            var_v0 = temp_v0 >> 5;
        }
        *(u32 *)(arg0 + 0x2D0) = var_v0;
    }
    temp_v1 = *(u32 *)(arg0 + 0x2CC) * 0x10;
    temp_a0_2 = *(u32 *)(arg0 + 0x2D0) * 0x10;
    *(s32 *)(arg0 + 0x3BC) = (s32)(temp_v1 >> 1);
    *(s32 *)(arg0 + 0x3C0) = (s32)(temp_a0_2 >> 1);
    *(s32 *)(arg0 + 0x3B4) = temp_v1;
    *(s32 *)(arg0 + 0x3B8) = temp_a0_2;
}
