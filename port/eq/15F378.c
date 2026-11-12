#include "common.h"

f32 Mathf_Asin(f32 arg0);
f32 atan2f(f32 arg0, f32 arg1);
extern f32 D_0038471C;
extern f32 D_00384720;

void func_0015F378(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    *(f32 *)(arg1 + 0x50) = Mathf_Asin(-*(f32 *)(temp_s0 + 0x34));
    temp_f0 = atan2f(*(f32 *)(temp_s0 + 0x30), *(f32 *)(temp_s0 + 0x38));
    *(f32 *)(arg1 + 0x54) = temp_f0;
    if (D_0038471C <= temp_f0) {
        *(f32 *)(arg1 + 0x54) = temp_f0 - D_00384720;
    }
    *(s32 *)(arg1 + 0x58) = 0;
}
