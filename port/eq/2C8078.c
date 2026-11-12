#include "common.h"

extern u8 D_0037A2D8[] __attribute__((section(".data")));

void func_002C8078(u8 *arg0, u8 *arg1) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_t1;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_t1;

    temp_t6 = (s16)*(s16 *)(arg0 + 0x1C) + (s16)*(s16 *)(arg0 + 0x1E);
    temp_t7 = *(s32 *)(arg0 + 0);
    temp_v1 = *(s32 *)(D_0037A2D8 + temp_t7 * 4);
    temp_v0 = (temp_t6 + (s32)((u32)temp_t6 >> 31)) >> 1;
    temp_t1 = *(s32 *)(arg0 + 0x14) + *(s32 *)(arg0 + 0x18) + 1 + temp_v0;
    var_t1 = temp_t1 % temp_v1;
    temp_a0 = *(s32 *)(arg0 + 0x10) + (temp_t1 / temp_v1);
    temp_hi = temp_a0 % 60;
    temp_a2 = *(s32 *)(arg0 + 0xC) + (temp_a0 / 60);
    temp_hi_2 = temp_a2 % 60;
    if ((*(s32 *)(arg0 + 4) != 0) && (temp_hi == 0) && ((temp_hi_2 % 10) != 0)) {
        var_t1 = ((u32)var_t1 < 2U) ? 2 : var_t1;
    }
    *(s32 *)(arg1 + 0) = temp_t7;
    *(s16 *)(arg1 + 0x1E) = (s16)(temp_t6 - (temp_v0 * 2));
    *(s32 *)(arg1 + 8) = *(s32 *)(arg0 + 8) + (temp_a2 / 60);
    *(s32 *)(arg1 + 4) = *(s32 *)(arg0 + 4);
    *(s32 *)(arg1 + 0xC) = temp_hi_2;
    *(s32 *)(arg1 + 0x10) = temp_hi;
    *(s32 *)(arg1 + 0x14) = var_t1;
}
