#include "common.h"

s32 func_002CBE18(void *arg0, void *arg1, s32 arg2);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0037A530[];

void func_002C9700(void *arg0, void *arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 *temp_a1;
    u8 *temp_s1;

    temp_s1 = (u8 *)arg0 + 0xD30;
    temp_a1 = (u8 *)arg1 + 0xC;
    *(s32 *)((u8 *)arg1 + 0x3C) = *(s32 *)(temp_a1 + 0x28);
    temp_a2 = *(s32 *)((u8 *)arg0 + 0xE6C);
    *(s32 *)((u8 *)arg1 + 0x38) = (*(s32 *)(temp_a1 + 0x24) - temp_a2) + *(s32 *)(temp_s1 + 0x164);
    temp_v1 = *(s32 *)(temp_a1 + 0x24);
    *(s32 *)((u8 *)arg1 + 0x4C) = temp_v1;
    *(s32 *)((u8 *)arg1 + 0x50) = temp_v1 + *(s32 *)(temp_s1 + 0x164);
    if (func_002CBE18(arg0, temp_a1, temp_a2) != 0) {
        temp_v0 = func_002E0A98(*(s32 *)((u8 *)arg1 + 0x3C),
                                (*(s32 *)((u8 *)arg1 + 0xE8) - *(s32 *)(temp_s1 + 0x160)) * 0x3E8,
                                D_0037A530[*(s32 *)((u8 *)arg1 + 0x6C)]);
        *(s32 *)((u8 *)arg1 + 0x4C) = temp_v0;
        temp_v0_2 = temp_v0 + *(s32 *)(temp_s1 + 0x164);
        *(s32 *)((u8 *)arg1 + 0x38) = temp_v0_2;
        *(s32 *)((u8 *)arg1 + 0x50) = temp_v0_2;
    }
    temp_v1_2 = *(s32 *)((u8 *)arg1 + 0x38);
    if (*(s32 *)(temp_s1 + 0x284) < temp_v1_2) {
        *(s32 *)(temp_s1 + 0x284) = temp_v1_2;
        *(s32 *)(temp_s1 + 0x288) = *(s32 *)((u8 *)arg1 + 0x3C);
    }
}
