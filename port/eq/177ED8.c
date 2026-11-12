#include "common.h"

void Mtx_InverseRT(s32 arg0, s32 arg1);
s32 func_00129C28(s32 arg0, s32 arg1);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void func_00129BB8(f32 farg0, s32 arg0, s32 arg1);
extern s32 gBtlCamView;

void func_00177ED8(u8 *arg0, u8 *arg1) {
    u8 fr[0x70];
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    f32 f20;
    f32 f21;

    s3 = arg0;
    s4 = arg1 + 0x10;
    s5 = arg0 + 0x10;
    s6 = arg0 + 0x30;
    s7 = arg1 + 0x20;
    s1 = fr + 0x10;
    s0 = fr + 0x20;

    Mtx_InverseRT((s32)(fr + 0x30), gBtlCamView);
    func_00129C28((s32)fr, (s32)(fr + 0x60));
    f21 = 0.5f;
    func_00129B58((s32)s1, (s32)fr, (s32)arg1);
    f20 = 1.0f;
    Vec3_Normalize((s32)s1, (s32)s1);
    Vec3_Cross((s32)s0, (s32)s7, (s32)s1);
    Vec3_Normalize((s32)s0, (s32)s0);
    func_00129BB8(*(f32 *)(arg1 + 0x38) * f21, (s32)s0, (s32)s0);
    func_00129B28((s32)s3, (s32)arg1, (s32)s0);
    func_00129B58((s32)s5, (s32)arg1, (s32)s0);
    *(f32 *)(s5 + 0xC) = f20;
    *(f32 *)(s3 + 0xC) = f20;
    func_00129B58((s32)s1, (s32)fr, (s32)s4);
    Vec3_Normalize((s32)s1, (s32)s1);
    Vec3_Cross((s32)s0, (s32)s7, (s32)s1);
    Vec3_Normalize((s32)s0, (s32)s0);
    func_00129BB8(*(f32 *)(arg1 + 0x38) * f21, (s32)s0, (s32)s0);
    func_00129B28((s32)(s3 + 0x20), (s32)s4, (s32)s0);
    func_00129B58((s32)s6, (s32)s4, (s32)s0);
    *(f32 *)(s6 + 0xC) = f20;
    *(f32 *)(s3 + 0x2C) = f20;
}
