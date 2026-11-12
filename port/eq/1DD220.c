#include "common.h"

s64 EftVram_AddClut(s32 arg0);
s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003878D4;

void func_001DD220(s32 arg0, s32 arg1) {
    u8 *p;
    s32 temp_v0;
    s64 temp_a0;
    u8 *temp_s1;

    p = (u8 *)arg0;
    temp_s1 = D_003878D4;
    temp_v0 = *(s32 *)((u8 *)arg1 + 4);
    if (!(*(s32 *)(temp_s1 + 0x8C) & (s32)(1u << (temp_v0 & 31)))) {
        *(s64 *)(p + 0xC0) = EftVram_AddImage(arg0 + 0xA0, 1, 0);
        temp_a0 = *(s64 *)(p + 0xC0) | ((s64)EftVram_AddClut(arg0 + 0xB0) << 37);
        *(s64 *)(p + 0xC0) = temp_a0;
        *(s64 *)(temp_s1 + (temp_v0 * 0x10) + 8) = temp_a0;
        *(s32 *)(temp_s1 + 0x8C) = *(s32 *)(temp_s1 + 0x8C) | (s32)(1u << (temp_v0 & 31));
        return;
    }
    *(s64 *)(p + 0xC0) = *(s64 *)(temp_s1 + (temp_v0 * 0x10) + 8);
}
