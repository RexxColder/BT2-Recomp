#include "common.h"

s64 EftVram_AddClut();
s64 EftVram_AddImage();
extern u8 *D_00387848;

void func_001AA638(u8 *arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    u8 *temp_s2;
    u8 *temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_v1;
    s32 var_v0;
    u8 *temp_a1;
    u8 *temp_s1;

    temp_a1 = *(u8 **)(arg0 + 0x38);
    temp_s0 = *(s32 *)(temp_a1 + 0x10);
    temp_s4 = temp_s0 * 0x10;
    temp_s2 = D_00387848 + 8 + (*(s32 *)(temp_a1 + 0x14) * 0x120);
    temp_s1 = temp_s2 + 8;
    temp_s3 = temp_s2 + 0x10;
    temp_v1 = *(s32 *)(temp_s1 + 0x10C);
    if (temp_v1 == 0) {
        *(s64 *)(temp_s1 + 0x118) = EftVram_AddImage(temp_s3, 1, 0);
        *(s64 *)(temp_s3 + temp_s4) = *(s64 *)(temp_s1 + 0x118) | (EftVram_AddClut(temp_s1 + temp_s4 + 8) << 0x25);
        var_v0 = *(s32 *)(temp_s1 + 0x10C) | (1 << temp_s0);
        goto block_5;
    }
    temp_s3_2 = 1 << temp_s0;
    if (!(temp_v1 & temp_s3_2)) {
        temp_s0_2 = temp_s0 * 0x10;
        *(s64 *)(temp_s2 + temp_s0_2 + 0x10) = *(s64 *)(temp_s1 + 0x118) | (EftVram_AddClut(temp_s1 + temp_s0_2 + 8, temp_a1) << 0x25);
        var_v0 = *(s32 *)(temp_s1 + 0x10C) | temp_s3_2;
block_5:
        *(s32 *)(temp_s1 + 0x10C) = var_v0;
    }
}
