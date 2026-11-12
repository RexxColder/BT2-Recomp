#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
s32 func_00129BB8(s32 arg0, s32 arg1, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
s32 BtlTask_SetDead(s32 arg0);

void func_001C7678(s32 arg0) {
    s32 sp[4];
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = *(s32 *)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(*(s32 *)*(s32 *)(temp_s0 + 0x64)) == 0) {
        func_00129BB8((s32)sp, temp_s0 + 0x40, 7.0f);
        func_00129B28(temp_s0 + 0x20, temp_s0 + 0x20, (s32)sp);
        temp_v0 = *(s32 *)(temp_s0 + 0x60) - 1;
        *(s32 *)(temp_s0 + 0x60) = temp_v0;
        if (temp_v0 <= 0) {
            BtlTask_SetDead(arg0);
        }
    }
}
