#include "common.h"

f32 Stg_CalcYaw(f32 farg0, f32 farg1, f32 farg2, f32 farg3, void *arg0, void *arg1, s32 arg2, void *arg3);
extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_00276B00(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *temp_v1;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_a2;
    s32 var_v0;

    var_v0 = -1;
    if ((gBtlStage != NULL) && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        temp_a2 = *(s32 *)(gBtlStage + 4);
        if (temp_a2 != 0) {
            temp_v1 = (u8 *)((s32)((u32)arg0 << 5) + temp_a2);
            temp_f20 = *(f32 *)(temp_v1 + 0xD0);
            temp_f21 = *(f32 *)(temp_v1 + 0xD8);
            temp_f0 = Stg_CalcYaw(temp_f20, temp_f21, *(f32 *)(temp_v1 + 0xE0), *(f32 *)(temp_v1 + 0xE8),
                                  temp_v1, temp_v1, temp_a2, gBtlStage);
            *(f32 *)(arg1 + 0) = temp_f20;
            var_v0 = 1;
            *(f32 *)(arg1 + 8) = temp_f21;
            *(f32 *)(arg1 + 0xC) = 1.0f;
            *(s32 *)(arg1 + 4) = 0;
            *(f32 *)(arg2 + 0xC) = 1.0f;
            *(f32 *)(arg2 + 4) = temp_f0;
            *(s32 *)(arg2 + 0) = 0;
            *(s32 *)(arg2 + 8) = 0;
        }
    }
    return var_v0;
}
