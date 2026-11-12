#include "common.h"

#define F32AT(p, off) (*(f32 *)((u8 *)(p) + (off)))

void func_00312638(void *arg0, void *arg1, void *arg2);
f32 Mathf_Cos(f32 farg0);
f32 func_0012A3F8(f32 farg0);
s32 func_0013B350(f32 *out);
extern f32 D_003841F4;
extern f32 D_003841F8;
extern u8 *gBtlCam;

s32 func_001304E0(void *arg0) {
    s32 sp[4];
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f5;
    f32 temp_f3;
    f32 temp_cos;
    f32 temp_sin;
    s32 idx;

    func_00312638(arg0, arg0, (u8 *)arg0 + 0x10);
    F32AT(arg0, 0x10) = F32AT(arg0, 0x10) + (F32AT(arg0, 0x10) * F32AT(arg0, 0x20));
    temp_f4 = F32AT(arg0, 0x34);
    temp_f5 = F32AT(arg0, 0x14);
    temp_f3 = F32AT(arg0, 0x18);
    temp_f0 = F32AT(arg0, 0x20);
    F32AT(arg0, 4) = F32AT(arg0, 4) + temp_f4;
    F32AT(arg0, 0x18) = temp_f3 + (temp_f3 * temp_f0);
    F32AT(arg0, 0x34) = temp_f4 + (temp_f4 * F32AT(arg0, 0x38));
    F32AT(arg0, 0x14) = temp_f5 + (temp_f5 * temp_f0);

    temp_cos = Mathf_Cos(F32AT(arg0, 0x3C));
    F32AT(arg0, 0) = F32AT(arg0, 0) + (temp_cos * F32AT(arg0, 0x40));
    temp_sin = func_0012A3F8(F32AT(arg0, 0x3C));
    temp_f4_2 = F32AT(arg0, 0x3C) + F32AT(arg0, 0x44);
    temp_f1_2 = F32AT(arg0, 8) + (temp_sin * F32AT(arg0, 0x40));
    F32AT(arg0, 0x3C) = temp_f4_2;
    F32AT(arg0, 8) = temp_f1_2;
    if (D_003841F4 < temp_f4_2) {
        F32AT(arg0, 0x3C) = temp_f4_2 - D_003841F8;
    }

    temp_f0_2 = F32AT(arg0, 0x2C) + F32AT(arg0, 0x30);
    F32AT(arg0, 0x2C) = temp_f0_2;
    if (temp_f0_2 <= 0.0f) {
        F32AT(arg0, 0x2C) = 0.0f;
        return 1;
    }
    if (func_0013B350(sp) == 0) {
        *(f32 *)sp = 5.0f;
    }
    if ((F32AT(arg0, 4) - (F32AT(arg0, 0x24) * 0.5f)) < *(f32 *)sp) {
        return 1;
    }
    idx = *(s32 *)((u8 *)arg0 + 0x4C);
    if (idx == -1) {
        return 0;
    }
    if (*(f32 *)(gBtlCam + (idx * 0x300) + 0x274) < *(f32 *)sp) {
        return 1;
    }
    return 0;
}
