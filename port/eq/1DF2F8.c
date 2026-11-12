#include "common.h"

extern s32 D_003878DC;

f32 func_001DF2F8(s32 arg0) {
    s32 temp_v0_2;
    u8 temp_v0;

    if (D_003878DC == 0) {
        goto defaults;
    }
    temp_v0_2 = *(s32 *)(D_003878DC + 0x218);
    if (temp_v0_2 == 0) {
        goto defaults;
    }
    *(s32 *)(arg0 + 0x0) = *(u8 *)(temp_v0_2 + 0);
    *(s32 *)(arg0 + 0x4) = *(u8 *)(temp_v0_2 + 1);
    *(s32 *)(arg0 + 0x8) = *(u8 *)(temp_v0_2 + 2);
    temp_v0 = *(u8 *)(temp_v0_2 + 3);
    *(s32 *)(arg0 + 0xC) = (s32)temp_v0;
    return (f32)temp_v0 / 255.0f;

defaults:
    *(s32 *)(arg0 + 0xC) = 0x80;
    *(s32 *)(arg0 + 0x8) = 0xF0;
    *(s32 *)(arg0 + 0x0) = 0xF0;
    *(s32 *)(arg0 + 0x4) = 0xF0;
    return 1.0f;
}
