#include "common.h"

s64 EftVram_AddClut(s32 arg0);
s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2);

void func_001947D8(s32 arg0, s32 arg1) {
    u8 *p;
    u8 *q;
    s32 temp_v1;
    u8 *temp_a3;
    u8 *temp_a3_2;
    u8 *temp_a1;
    s64 temp_a0;

    p = (u8 *)arg0;
    q = (u8 *)arg1;
    temp_a3 = *(u8 **)(q + 0x34);
    temp_v1 = *(s32 *)(q + 0x30);
    temp_a3_2 = temp_a3 + (temp_v1 * 0x10);
    if (!(*(s32 *)(temp_a3 + 0x104) & (s32)(1u << (temp_v1 & 31)))) {
        *(s64 *)(p + 0x1E8) = EftVram_AddImage(arg0 + 0x1C8, 1, 0);
        temp_a0 = *(s64 *)(p + 0x1E8) | ((s64)EftVram_AddClut(arg0 + 0x1D8) << 37);
        *(s64 *)(p + 0x1E8) = temp_a0;
        *(s64 *)(*(u8 **)(q + 0x34) + (*(s32 *)(q + 0x30) * 0x10)) = temp_a0;
        temp_a1 = *(u8 **)(q + 0x34);
        *(s32 *)(temp_a1 + 0x104) = *(s32 *)(temp_a1 + 0x104) | (s32)(1u << (*(s32 *)(q + 0x30) & 31));
    } else {
        *(s64 *)(p + 0x1E8) = *(s64 *)temp_a3_2;
    }
}
