#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
void func_0019CFA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0019CC50(s32 arg0) {
    u16 temp_v0;
    u16 temp_v1;
    s32 temp_a1;

    temp_a1 = *(s32 *)(arg0 + 0x38);
    temp_v0 = *(u16 *)(temp_a1 + 0xC24);
    temp_v1 = temp_v0 | 0x20;
    if ((temp_v0 & 0x20) == 0) {
        *(u16 *)(temp_a1 + 0xC24) = temp_v1;
        if ((temp_v1 & 0x40) != 0) {
            func_0019CFA0(arg0, *(s32 *)temp_a1, *(s32 *)(temp_a1 + 0xC1C), 0);
        }
    }
    BtlTask_SetDead(arg0);
}
