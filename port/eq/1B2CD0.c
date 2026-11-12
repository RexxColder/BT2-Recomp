#include "common.h"

s64 EftVram_AddClut(void *arg0);
s64 EftVram_AddImage(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_00387870;

void func_001B2CD0(u8 *arg0, u8 *arg1) {
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_s0;
    u8 *temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s64 temp_a0;

    temp_a1 = *(u8 **)(arg1 + 0x34);
    if (temp_a1 == NULL) {
        temp_s0 = D_00387870 + 0x18;
        temp_s2 = D_00387870 + 0x10;
        temp_v1 = *(s32 *)(temp_s0 + 0x104);
        if (temp_v1 == 0) {
            *(s64 *)(temp_s2 + 0x110) = EftVram_AddImage(temp_s0, 1, 0);
            *(s64 *)(temp_s0 + (*(s32 *)(arg1 + 4) * 0x10)) =
                *(s64 *)(temp_s2 + 0x110) | (EftVram_AddClut(temp_s0 + (*(s32 *)(arg1 + 4) * 0x10)) << 0x25);
            *(s32 *)(temp_s0 + 0x104) = *(s32 *)(temp_s0 + 0x104) | (1 << *(s32 *)(arg1 + 4));
            return;
        }
        temp_v0 = *(s32 *)(arg1 + 4);
        if (!(temp_v1 & (1 << temp_v0))) {
            *(s64 *)(temp_s0 + (temp_v0 * 0x10)) =
                *(s64 *)(temp_s2 + 0x110) | (EftVram_AddClut(temp_s0 + (temp_v0 * 0x10)) << 0x25);
            *(s32 *)(temp_s0 + 0x104) = *(s32 *)(temp_s0 + 0x104) | (1 << *(s32 *)(arg1 + 4));
        }
    } else {
        temp_v0_2 = *(s32 *)(arg1 + 0x30);
        if (!(*(s32 *)(temp_a1 + 0x104) & (1 << temp_v0_2))) {
            *(s64 *)(arg0 + 0xAA8) = EftVram_AddImage(arg0 + 0xA88, 1, 0);
            temp_a0 = *(s64 *)(arg0 + 0xAA8) | (EftVram_AddClut(arg0 + 0xA98) << 0x25);
            *(s64 *)(arg0 + 0xAA8) = temp_a0;
            temp_a1_2 = *(u8 **)(arg1 + 0x34);
            *(s64 *)(temp_a1_2 + (*(s32 *)(arg1 + 0x30) * 0x10)) = temp_a0;
            *(s32 *)(temp_a1_2 + 0x104) = *(s32 *)(temp_a1_2 + 0x104) | (1 << *(s32 *)(arg1 + 0x30));
            return;
        }
        *(s64 *)(arg0 + 0xAA8) = *(s64 *)(temp_a1 + (temp_v0_2 * 0x10));
    }
}
