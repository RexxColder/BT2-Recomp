#include "common.h"

s32 BtlCtrl_IsInterruptible(s32 arg0);
void EftTechEvt_RequestExpire(s32 arg0);
void BtlTask_SetDead(s32 arg0);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129DE0(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
f32 func_001A8018(s32 arg0);
void func_001A8A78(s32 arg0);
f32 func_0020A150(void);

void func_001A8060(s32 arg0) {
    s32 sp[4];
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 var_f12;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s4;
    s32 temp_s5;

    temp_s2 = *(s32 *)(arg0 + 0x38);
    *(s32 *)(temp_s2 + 0x24) = *(s32 *)(temp_s2 + 0x24) + 1;
    if ((BtlCtrl_IsInterruptible(0) == 0) || (BtlCtrl_IsInterruptible(1) == 0)) {
        *(s32 *)(temp_s2 + 0x28) = *(s32 *)(temp_s2 + 0x28) | 1;
    }
    if (*(s32 *)(temp_s2 + 0x28) & 1) {
        EftTechEvt_RequestExpire(0);
        EftTechEvt_RequestExpire(1);
        BtlTask_SetDead(arg0);
        return;
    }
    temp_s4 = temp_s2 + 0x60;
    temp_s5 = temp_s2 + 0x1E0;
    temp_f0 = (func_0020A150() + 1.0f) * 0.5f;
    *(f32 *)(temp_s2 + 0x20) = temp_f0;
    if (temp_f0 < 0.0f) {
        *(f32 *)(temp_s2 + 0x20) = 0.0f;
    }
    var_f12 = *(f32 *)(temp_s2 + 0x20);
    temp_s1 = temp_s2 + 0x1F0;
    if (var_f12 > 1.0f) {
        *(f32 *)(temp_s2 + 0x20) = 1.0f;
        var_f12 = 1.0f;
    }
    temp_s0 = temp_s2 + 0x70;
    func_00129DE0(var_f12, temp_s2, temp_s1, temp_s0);
    *(f32 *)(temp_s2 + 0xC) = 1.0f;
    temp_f20 = func_001A8018(temp_s4);
    func_00129B58((s32)sp, temp_s0, temp_s2);
    Vec3_Normalize((s32)sp, (s32)sp);
    func_00129BD0((s32)sp, (s32)sp, temp_f20);
    Vec3_Add(*(s32 *)(temp_s4 + 0x60) + 0x10, temp_s2, (s32)sp);
    temp_f20_2 = func_001A8018(temp_s5);
    func_00129B58((s32)sp, temp_s1, temp_s2);
    Vec3_Normalize((s32)sp, (s32)sp);
    func_00129BD0((s32)sp, (s32)sp, temp_f20_2);
    Vec3_Add(*(s32 *)(temp_s5 + 0x60) + 0x10, temp_s2, (s32)sp);
    func_001A8A78(arg0);
}
