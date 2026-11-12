#include "common.h"

s32 BtlStage_IsReady(void);
void BtlStage_ProbeGround(s32 arg0, s32 arg1, s32 arg2);
f32 Stg_CalcYaw(f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern u8 *gBtlStage;

void func_00276700(u8 *arg0, u8 *arg1) {
    s32 sp[12];
    f32 temp_f0;
    u8 *temp_s0;

    BtlStage_IsReady();
    temp_s0 = *(u8 **)(gBtlStage + 4);
    temp_f0 = Stg_CalcYaw(*(f32 *)(temp_s0 + 0xB0), *(f32 *)(temp_s0 + 0xB8), *(f32 *)(temp_s0 + 0xC0), *(f32 *)(temp_s0 + 0xC8));
    *(f32 *)(arg0 + 0) = *(f32 *)(temp_s0 + 0xB0);
    *(f32 *)(arg0 + 4) = -700.0f;
    *(f32 *)(arg0 + 0xC) = 1.0f;
    *(f32 *)(arg0 + 8) = *(f32 *)(temp_s0 + 0xB8);
    *(f32 *)(arg1 + 0xC) = 1.0f;
    *(f32 *)(arg1 + 4) = temp_f0;
    *(s32 *)(arg1 + 0) = 0;
    *(s32 *)(arg1 + 8) = 0;
    BtlStage_ProbeGround(-1, (s32)arg0, (s32)sp);
    *(f32 *)(arg0 + 4) = ((f32 *)sp)[1];
}
