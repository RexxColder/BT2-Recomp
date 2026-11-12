#include "common.h"

extern u8 *gBtlStage;

void func_002768A8(u8 *arg0, s32 arg1) {
    u8 *temp_v1;
    u8 *temp_a1;

    temp_v1 = *(u8 **)(gBtlStage + 4);
    temp_a1 = (temp_v1 + (*(s32 *)(temp_v1 + 0xC) * 4)) + (arg1 * 0x10);
    *(s32 *)(arg0 + 8) = *(s32 *)(temp_a1 + 0);
    *(s32 *)(arg0 + 0x34) = *(s32 *)(temp_a1 + 4);
}
