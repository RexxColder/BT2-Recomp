#include "common.h"

s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 BtlObjXf_Update(u8 *a0);
s32 func_001FA0A0(u8 *a0, s32 a1, s32 a2);
s32 func_001FA110(u8 *a0, s32 a1);
s32 func_001F9D78(u8 *a0, s32 a1);
void BtlAnim_SetBlend(f32 farg0, u8 *a0);
s32 func_0023F410(u8 *a0);
u8 *BtlChar_GetPos(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_001F9D68(f32 farg0, u8 *a0);
void func_001F9D10(u8 *a0, s32 a1);
f32 func_00240D50(u8 *a0, s32 a1);
void func_00215068(s32 a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 a1, s32 a2);
void func_00216208(s32 a0, f32 farg0, f32 farg1);
void func_002166C0(u8 *a0);
void func_00216678(u8 *a0);
void func_0020D7E8(u8 *a0, f32 farg0, f32 farg1);
void func_00206958(u8 *a0, s64 a1);
f32 atan2f(f32 y, f32 x);
f32 sinf(f32 x);
extern f32 D_00386398;
extern f32 D_0038639C;
extern f32 D_003863A0;
extern f32 D_003863A4;
extern f32 D_003863A8;
extern f32 D_003863AC;
extern f32 D_003863B0;

void func_00228398(u8 *arg0) {
    s32 temp_s0_2;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f12;
    f32 temp_f20;
    f32 var_f0;
    f32 var_f0_2;
    s32 temp_v0;
    s32 var_condition_bit;
    u8 *temp_s0;

    if (func_00211310(arg0, 0, 4) != 0) {
        func_002113C0(arg0, 0, 2, 0);
    }
    temp_v0 = BtlObjXf_Update(arg0);
    if (temp_v0 == 2) {
        func_001FA0A0(arg0, 3, 0);
    } else if (temp_v0 == 0x1A4) {
        func_001FA110(arg0, 0);
        if (func_00211310(arg0, 0, 0x104) != 0) {
            BtlAnim_SetBlend(D_0038639C, arg0);
            func_001F9D78(arg0, 3);
        }
    } else if (temp_v0 == 3) {
        func_001FA110(arg0, 0);
        if ((func_0023F410(arg0) & 0x1000) && (func_00211310(arg0, 0, 2) != 0) && (func_00211310(arg0, 0, 0x100) == 0)) {
            BtlAnim_SetBlend(D_00386398, arg0);
            func_001F9D78(arg0, 0x1A4);
        }
    }
    if (BtlObjXf_Update(arg0) != 0x1A4) {
        temp_s0 = BtlChar_GetPos(arg0);
        BtlChar_GetPos(arg0);
        temp_f0 = sinf(BtlUtil_WrapAngle(atan2f(*(f32 *)(temp_s0 + 0x20), *(f32 *)(temp_s0 + 0x28)) - *(f32 *)(arg0 + 0x150)));
        temp_f1 = *(f32 *)(arg0 + 0x8D0);
        if (temp_f1 < temp_f0) {
            var_f0 = temp_f1 + D_003863A0;
            var_condition_bit = temp_f0 < var_f0;
        } else {
            var_f0 = temp_f1 - D_003863A4;
            var_condition_bit = var_f0 < temp_f0;
        }
        *(f32 *)(arg0 + 0x8D0) = var_f0;
        if (var_condition_bit) {
            *(f32 *)(arg0 + 0x8D0) = temp_f0;
        }
        temp_f12 = *(f32 *)(arg0 + 0x8D0);
        if (!(temp_f12 > 0.0f)) {
            func_001F9D68(-temp_f12, arg0);
            temp_v0 = BtlObjXf_Update(arg0);
            if (temp_v0 == 2) {
                func_001F9D10(arg0, 5);
            } else if (temp_v0 == 3) {
                func_001F9D10(arg0, 6);
            }
        } else {
            func_001F9D68(temp_f12, arg0);
            temp_v0 = BtlObjXf_Update(arg0);
            if (temp_v0 == 2) {
                func_001F9D10(arg0, 8);
            } else if (temp_v0 == 3) {
                func_001F9D10(arg0, 9);
            }
        }
    }
    temp_s0_2 = (func_00211310(arg0, 0, 2) == 0) ? 2 : 3;
    if (func_00211310(arg0, 0, 0x100) != 0) {
        var_f0_2 = func_00240D50(arg0, 1);
    } else {
        var_f0_2 = func_00240D50(arg0, 0);
    }
    temp_f20 = D_003863A8;
    func_00215068((s32)arg0, 0, 0xA, D_003863AC, temp_f20);
    func_00215E88(temp_f20, (s32)arg0, temp_s0_2);
    func_00216208((s32)arg0, var_f0_2, D_003863B0);
    if (BtlObjXf_Update(arg0) == 0x1A4) {
        func_002166C0(arg0);
    } else {
        func_00216678(arg0);
    }
    func_002113C0(arg0, 9, 0x80000, 1);
    func_0020D7E8(arg0, 20.0f, 50.0f);
    func_002113C0(arg0, 9, 0x40, 1);
    func_002113C0(arg0, 1, 0x400, 1);
    func_002113C0(arg0, 1, 0x10000, 1);
    func_002113C0(arg0, 1, 0x400000, 1);
    if (func_00211310(arg0, 0, 4) != 0) {
        func_00206958(arg0, (s64)0x8000 << 17);
    }
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
