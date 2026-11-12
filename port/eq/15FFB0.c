#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void EftTechEvt_RequestStop(s32 arg0);
void func_00129C38(u8 *arg0, u8 *arg1);

void func_0015FFB0(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s2 = *(u8 **)(temp_s0 + 0xF0);
    if (BtlScene_IsCharStopped(*(s32 *)temp_s2) == 0) {
        *(s32 *)(temp_s0 + 0) = *(s32 *)(temp_s0 + 0) & ~0x20;
        if (*(u16 *)(arg0 + 8) & 1 & 0xFFFF) {
            func_00129C38(temp_s0 + 0x80, arg0 + 0x10);
            *(s32 *)(temp_s0 + 0) = *(s32 *)(temp_s0 + 0) | 0x20;
        }
        temp_v1 = *(s32 *)(arg0 + 4);
        temp_v0 = temp_v1 & 2;
        if (temp_v1 & 1) {
            if (temp_v0 == 0) {
                EftTechEvt_RequestStop(*(s32 *)temp_s2);
                var_v0 = (*(s32 *)(temp_s0 + 0) & ~0x10) | 0x200;
            } else {
                goto block_9;
            }
            goto block_10;
        }
        if ((temp_v0 != 0) || (temp_v1 & 4)) {
block_9:
            var_v0 = (*(s32 *)(temp_s0 + 0) | 0x100) & ~0x10;
block_10:
            *(s32 *)(temp_s0 + 0) = var_v0;
        }
        if (*(u16 *)(arg0 + 8) & 4) {
            *(s32 *)(temp_s0 + 0) = (*(s32 *)(temp_s0 + 0) | 1) & ~0x10;
        }
    }
}
