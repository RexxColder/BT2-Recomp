#include "common.h"

s32 BtlScene_IsTimeStopped(s32 arg0);
void BtlTask_SetDead(s32 arg0);
void EftPtcl3_SetPos(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

void func_001A1588(u8 *arg0) {
    f32 temp_f0;
    s32 temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsTimeStopped((s32)arg0) == 0) {
        temp_s0 = (s32)(temp_s1 + 0x10);
        func_00208DE8(*(s32 *)temp_s1, temp_s0, 3);
        EftPtcl3_SetPos(*(s32 *)(temp_s1 + 0x2C), temp_s0);
        temp_f0 = *(f32 *)(temp_s1 + 0x20) - 1.0f;
        *(f32 *)(temp_s1 + 0x20) = temp_f0;
        if (temp_f0 <= 0.0f) {
            *(s32 *)(temp_s1 + 0x28) = *(s32 *)(temp_s1 + 0x28) | 1;
        }
        if (*(s32 *)(temp_s1 + 0x28) & 1) {
            BtlTask_SetDead((s32)arg0);
        }
    }
}
