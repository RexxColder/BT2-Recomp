#include "common.h"

s32 BtlStage_IsReady(void);
void BtlStage_ProbeGround(s32 arg0, s32 arg1, s32 arg2);
f32 Stg_CalcYaw(f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern u8 *gBtlStage;

void func_002765A8(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 sp[12];
    u8 *s1;
    f32 yaw;
    f32 lastf;

    BtlStage_IsReady();
    s1 = *(u8 **)(gBtlStage + 4);
    if ((arg3 & 0xFF) == 1) {
        yaw = Stg_CalcYaw(*(f32 *)(s1 + 0x90), *(f32 *)(s1 + 0x98), *(f32 *)(s1 + 0xA0), *(f32 *)(s1 + 0xA8));
        *(f32 *)(arg1 + 0) = *(f32 *)(s1 + 0x90);
        *(f32 *)(arg1 + 4) = -700.0f;
        lastf = *(f32 *)(s1 + 0x98);
    } else if (arg0 != 0) {
        yaw = Stg_CalcYaw(*(f32 *)(s1 + 0x70), *(f32 *)(s1 + 0x78), *(f32 *)(s1 + 0x80), *(f32 *)(s1 + 0x88));
        *(f32 *)(arg1 + 0) = *(f32 *)(s1 + 0x70);
        *(f32 *)(arg1 + 4) = -700.0f;
        lastf = *(f32 *)(s1 + 0x78);
    } else {
        yaw = Stg_CalcYaw(*(f32 *)(s1 + 0x50), *(f32 *)(s1 + 0x58), *(f32 *)(s1 + 0x60), *(f32 *)(s1 + 0x68));
        *(f32 *)(arg1 + 0) = *(f32 *)(s1 + 0x50);
        *(f32 *)(arg1 + 4) = -700.0f;
        lastf = *(f32 *)(s1 + 0x58);
    }
    *(f32 *)(arg1 + 8) = lastf;
    *(f32 *)(arg1 + 0xC) = 1.0f;
    *(f32 *)(arg2 + 4) = yaw;
    *(f32 *)(arg2 + 0xC) = 1.0f;
    *(s32 *)(arg2 + 0) = 0;
    *(s32 *)(arg2 + 8) = 0;
    BtlStage_ProbeGround(-1, (s32)arg1, (s32)sp);
    *(f32 *)(arg1 + 4) = *(f32 *)((u8 *)sp + 4);
}
