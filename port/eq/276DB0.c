#include "common.h"

f32 Stg_CalcYaw(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_00276DB0(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    s32 var_v0;
    u8 *temp_s0;

    var_v0 = 0;
    if (gBtlStage != NULL) {
        if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
            temp_s0 = *(u8 **)(gBtlStage + 4);
            if (temp_s0 != NULL) {
                temp_f0 = Stg_CalcYaw((s32)D_003876A0, (s32)arg1, (s32)gBtlStage,
                                      *(f32 *)(temp_s0 + 0x50), *(f32 *)(temp_s0 + 0x58),
                                      *(f32 *)(temp_s0 + 0x60), *(f32 *)(temp_s0 + 0x68));
                *(s32 *)(arg0 + 4) = 0;
                var_v0 = 1;
                *(f32 *)(arg0 + 0) = *(f32 *)(temp_s0 + 0x50);
                *(f32 *)(arg0 + 0xC) = 1.0f;
                *(f32 *)(arg0 + 8) = *(f32 *)(temp_s0 + 0x58);
                *(f32 *)(arg1 + 0xC) = 1.0f;
                *(f32 *)(arg1 + 4) = temp_f0;
                *(s32 *)(arg1 + 0) = 0;
                *(s32 *)(arg1 + 8) = 0;
            }
        }
    }
    return var_v0;
}
