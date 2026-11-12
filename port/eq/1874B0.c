#include "common.h"

s64 EftVram_AddClut(u8 *arg0);
s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);

void func_001874B0(u8 *arg0) {
    s64 temp_a1_2;
    u8 temp_v0;
    u8 *temp_a1;
    u8 *temp_a0;

    temp_a1 = *(u8 **)arg0;
    if (temp_a1 != NULL) {
        temp_v0 = arg0[0x198];
        if (!(*(s32 *)(temp_a1 + 0x104) & (s32)(1u << (temp_v0 & 31)))) {
            temp_a1_2 = EftVram_AddImage(arg0 + 8, 1, 0);
            *(s64 *)(arg0 + 0x28) = temp_a1_2;
            temp_a1_2 = temp_a1_2 | (s64)((u64)EftVram_AddClut(arg0 + 0x18) << 37);
            *(s64 *)(arg0 + 0x28) = temp_a1_2;
            *(s64 *)(*(u8 **)arg0 + arg0[0x198] * 0x10) = temp_a1_2;
            temp_a0 = *(u8 **)arg0;
            *(s32 *)(temp_a0 + 0x104) = *(s32 *)(temp_a0 + 0x104) | (s32)(1u << (arg0[0x198] & 31));
            return;
        }
        *(s64 *)(arg0 + 0x28) = *(s64 *)(temp_a1 + temp_v0 * 0x10);
    }
}
