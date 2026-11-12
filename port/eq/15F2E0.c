#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
extern f32 D_00384710;
extern f32 D_00384714;
extern u32 D_00384718;

void func_0015F2E0(u8 *arg0, u8 *arg1) {
    u8 *temp_s0;
    f32 temp_f0;

    temp_s0 = (u8 *)*(s32 *)(arg0 + 0x38);
    func_00129C28((s32)(arg1 + 0x40), (s32)(temp_s0 + 0x40));
    *(f32 *)(arg1 + 0x50) = Mathf_Asin(-*(f32 *)(temp_s0 + 0x34));
    temp_f0 = atan2f(*(f32 *)(temp_s0 + 0x30), *(f32 *)(temp_s0 + 0x38));
    *(f32 *)(arg1 + 0x54) = temp_f0;
    if (D_00384710 <= temp_f0) {
        *(f32 *)(arg1 + 0x54) = temp_f0 - D_00384714;
    }
    *(u32 *)(arg1 + 0x38) = D_00384718;
    *(f32 *)(arg1 + 0x3C) = 1.0f;
    *(s32 *)(arg1 + 0x58) = 0;
    *(s32 *)(arg1 + 0x60) = 0;
    *(s32 *)(arg1 + 0x64) = 0;
    *(s32 *)(arg1 + 0x68) = 0;
}
