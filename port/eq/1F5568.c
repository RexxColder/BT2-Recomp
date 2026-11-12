#include "common.h"

void BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 func_00148A80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001F5568(s32 arg0, u8 **arg1) {
    u8 *temp_a1;
    u32 temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_a1 = *arg1;
    if (temp_a1 != NULL) {
        temp_v0 = *(u32 *)(temp_a1 + 4);
        if (*(u32 *)(temp_a1 + 8) != temp_v0) {
            temp_v1 = temp_a1 + ((temp_v0 >> 2) * 4);
            temp_v1_2 = temp_v1 + (((u32)*(u32 *)(temp_v1 + 4) >> 2) * 4);
            *(s16 *)(temp_v1_2 + 0x48) = -1;
            *(s32 *)(temp_v1_2 + 0) = 0x172;
            *(s16 *)(temp_v1_2 + 0x3E) = -1;
            *(s16 *)(temp_v1_2 + 0x40) = -1;
            *(s16 *)(temp_v1_2 + 0x42) = -1;
            *(s16 *)(temp_v1_2 + 0x44) = -1;
            *(s16 *)(temp_v1_2 + 0x46) = -1;
            func_00148A80(1, 2, (s32)temp_v1, -1);
            BtlTask_CreateChildList(arg0, 1, 0);
        }
    }
}
