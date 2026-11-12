#include "common.h"

s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void func_00148A80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001F53F8(s32 arg0, s32 arg1) {
    s32 temp_a3;
    u32 temp_v0;
    u8 *temp_a1;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_a1 = *(u8 **)arg1;
    if (temp_a1 != 0) {
        temp_v0 = *(u32 *)(temp_a1 + 0x08);
        if (*(u32 *)(temp_a1 + 0x0C) != temp_v0) {
            temp_v1 = temp_a1 + ((temp_v0 >> 2) * 4);
            temp_v1_2 = temp_v1 + ((*(u32 *)(temp_v1 + 0x04) >> 2) * 4);
            *(s16 *)(temp_v1_2 + 0x48) = -1;
            temp_a3 = *(s32 *)(temp_v1_2 + 0x30) | 0x2000;
            *(s32 *)(temp_v1_2 + 0x00) = 0x175;
            *(s32 *)(temp_v1_2 + 0x30) = temp_a3;
            *(s32 *)(temp_v1_2 + 0x08) = 1;
            *(s32 *)(temp_v1_2 + 0x04) = 1;
            *(s32 *)(temp_v1_2 + 0x20) = 0;
            *(s16 *)(temp_v1_2 + 0x3E) = -1;
            *(s16 *)(temp_v1_2 + 0x40) = -1;
            *(s16 *)(temp_v1_2 + 0x42) = -1;
            *(s16 *)(temp_v1_2 + 0x44) = -1;
            *(s16 *)(temp_v1_2 + 0x46) = -1;
            func_00148A80(1, 2, (s32)temp_v1, temp_a3);
            BtlTask_CreateChildList(arg0, 1, 0);
        }
    }
}
