#include "m2c_macros.h"

extern void Mtx_InverseRT(s32 arg0, s32 arg1);
extern void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
extern void Vec3_Normalize(s32 arg0, s32 arg1);
extern void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
extern void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
extern void func_00129BB8(f32 farg0, s32 arg1, s32 arg2);
extern s32 func_00129C28(s32 arg0, s32 arg1);
extern s32 gBtlCamView;

void func_00177D58(u8 *arg0, u8 *arg1) {
    u8 spf[0xA0] __attribute__((aligned(16)));
#define sp10 ((s32 *)(spf + 0x10))
#define sp20 ((s32 *)(spf + 0x20))
#define sp30 ((s32 *)(spf + 0x30))
#define sp60 ((s32 *)(spf + 0x60))
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *s7;

    s2 = arg1;
    s4 = arg0;
    s3 = s2 + 0x10;
    s5 = s4 + 0x10;
    s6 = s2 + 0x20;
    s7 = s4 + 0x30;
    Mtx_InverseRT((s32)sp30, gBtlCamView);
    func_00129C28((s32)sp10, (s32)sp60);
    s1 = (u8 *)sp10;
    func_00129B58((s32)s1, (s32)sp10, (s32)s3);
    Vec3_Normalize((s32)s1, (s32)s1);
    s0 = (u8 *)sp20;
    Vec3_Cross((s32)s0, (s32)s6, (s32)s1);
    Vec3_Normalize((s32)s0, (s32)s0);
    func_00129BB8(*(f32 *)(s2 + 0x34), (s32)s0, (s32)s0);
    func_00129B28((s32)s4, (s32)s3, (s32)s0);
    func_00129B58((s32)s5, (s32)s3, (s32)s0);
    *(f32 *)(s5 + 0xC) = 1.0f;
    *(f32 *)(s4 + 0xC) = 1.0f;
    func_00129B58((s32)s1, (s32)sp10, (s32)s2);
    Vec3_Normalize((s32)s1, (s32)s1);
    Vec3_Cross((s32)s0, (s32)s6, (s32)s1);
    Vec3_Normalize((s32)s0, (s32)s0);
    func_00129BB8(*(f32 *)(s2 + 0x34), (s32)s0, (s32)s0);
    func_00129B28((s32)(s4 + 0x20), (s32)s2, (s32)s0);
    func_00129B58((s32)s7, (s32)s2, (s32)s0);
    *(f32 *)(s7 + 0xC) = 1.0f;
    *(f32 *)(s4 + 0x2C) = 1.0f;
}
