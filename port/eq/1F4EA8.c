#include "common.h"

s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void func_00148A80(s32 arg0, s32 arg1, void *arg2, s32 arg3);

void func_001F4EA8(s32 arg0, u8 **arg1) {
    u8 *temp_a1;
    u32 temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    s32 temp_a3;

    temp_a1 = *arg1;
    if (temp_a1 != NULL) {
        temp_v0 = *(u32 *)(temp_a1 + 4);
        if (*(s32 *)(temp_a1 + 8) != (s32)temp_v0) {
            temp_v0_2 = temp_a1 + ((temp_v0 >> 2) * 4);
            temp_v0_3 = temp_v0_2 + ((*(u32 *)(temp_v0_2 + 4) >> 2) * 4);
            *(s8 *)(temp_v0_3 + 0x3D) = 0x2D;
            temp_a3 = *(s32 *)(temp_v0_3 + 0x30) | 4;
            *(s32 *)temp_v0_3 = 0x16E;
            *(s32 *)(temp_v0_3 + 0x30) = temp_a3;
            *(s16 *)(temp_v0_3 + 0x48) = -1;
            *(s16 *)(temp_v0_3 + 0x3E) = -1;
            *(s16 *)(temp_v0_3 + 0x40) = -1;
            *(s16 *)(temp_v0_3 + 0x42) = -1;
            *(s16 *)(temp_v0_3 + 0x44) = -1;
            *(s16 *)(temp_v0_3 + 0x46) = -1;
            *(s8 *)(temp_v0_3 + 0x38) = 0x2D;
            *(s8 *)(temp_v0_3 + 0x39) = 0x2D;
            *(s8 *)(temp_v0_3 + 0x3A) = 0x2D;
            *(s8 *)(temp_v0_3 + 0x3B) = 0x2D;
            *(s8 *)(temp_v0_3 + 0x3C) = 0x2D;
            func_00148A80(0, 2, temp_v0_2, temp_a3);
            BtlTask_CreateChildList(arg0, 1, 0);
        }
    }
}
