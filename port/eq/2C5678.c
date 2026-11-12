#include "common.h"

void func_002C5678(u8 *arg0, u8 *arg1) {
    s32 temp_v0;
    s32 temp_t1;
    s32 temp_t0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_a3;
    s32 temp_a2;
    s32 temp_a3_2;
    s32 temp_t1_2;
    s32 temp_a2_2;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_t2;
    s32 temp_v1_2;

    temp_v1 = *(s32 *)(arg0 + 0x0);
    temp_t2 = *(s32 *)(arg0 + 0x4);
    temp_v0 = temp_v1 + 0xF;
    temp_t1 = temp_t2 + 0xF;
    temp_v0_2 = ((temp_v0 < 0) ? (temp_v1 + 0x1E) : temp_v0) >> 4;
    temp_t0 = (s32)((u32)temp_v0_2 << 4);
    temp_v0_3 = (s32)((u32)temp_v0_2 << 3);
    temp_a3 = temp_t0 + 0x3F;
    temp_a2 = temp_v0_3 + 0x3F;
    temp_v1_2 = *(s32 *)(arg0 + 0x20);
    temp_a3_2 = ((temp_a3 < 0) ? (temp_t0 + 0x7E) : temp_a3) >> 6;
    temp_t1_2 = ((temp_t1 < 0) ? (temp_t2 + 0x1E) : temp_t1) >> 4;
    temp_a2_2 = ((temp_a2 < 0) ? (temp_v0_3 + 0x7E) : temp_a2) >> 6;
    *(s16 *)(arg1 + 0xE) = (s16)((u32)temp_a3_2 << 6);
    *(s16 *)(arg1 + 0xC) = (s16)((u32)temp_a2_2 << 6);
    *(s32 *)(arg1 + 0x8) = temp_v1_2;
    temp_v0_4 = temp_v1_2 + (s32)((u32)(temp_a3_2 * temp_t1_2) << 10);
    *(s32 *)(arg1 + 0x0) = temp_v0_4;
    *(s32 *)(arg1 + 0x4) = temp_v0_4 + (s32)((u32)(temp_a2_2 * temp_t1_2) << 9);
}
