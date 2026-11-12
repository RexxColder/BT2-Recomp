#include "common.h"

void BtlOpp_GetDelta(s32 arg0, f32 *arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 func_001A7DA8(void);
u8 *func_00211288(s32 arg0);
void func_00208DE8(s32 arg0, f32 *arg1, s32 arg2);
void sceVu0InterVector(f32 farg0, f32 *arg1, f32 *arg2, f32 *arg3);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
void func_001FC3B0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
    s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_003859D0;
extern f32 D_003859D4;
extern f32 D_003859D8;

void func_0020EEF8(s32 arg0, f32 farg0) {
    f32 sp30[4];
    f32 sp40[4];
    f32 sp50[4];
    f32 sp60[4];
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    u8 *ptr;

    BtlOpp_GetDelta((s32)func_00211288(0), sp30);
    temp_f20 = farg0 * D_003859D0;
    sceVu0Normalize(sp30, sp30);
    func_00208DE8(0, sp50, 0x11);
    func_00208DE8(1, sp60, 0x11);
    temp_f20 = temp_f20 * 0.5f;
    sceVu0InterVector((farg0 * D_003859D4) + 0.5f, sp40, sp60, sp50);
    temp_f20 = temp_f20 + D_003859D8;
    temp_f22 = BtlUtil_WrapAngle(atan2f(sp30[0], sp30[2]) + temp_f20);
    temp_f20 = -Mathf_Asin(sp30[1]);
    temp_f21 = func_001A7DA8();
    temp_f20 = temp_f20 * farg0;
    ptr = func_00211288(0);
    func_001FC3B0(temp_f22, 0.0f, temp_f20, 0.0f, temp_f21 + 50.0f, 0.0f,
        (s32)ptr, arg0, (s32)D_002C3630, arg0, (s32)D_002C3630, (s32)sp40, (s32)D_002C3630,
        -1, -1, -1, -1, 1, 0x45);
}
