#include "common.h"

extern s32 gBtlCamView;

f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
s32 func_001267E8(s32 arg0, s32 arg1);
s32 func_00126598(s32 arg0);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_RotateY(f32 farg0, s32 arg0, s32 arg1);
void func_00128EF0(void);
void func_00128F90(s32 arg0);
void func_00128F08(void);
void func_00193470(s32 arg0, s32 arg1, s32 arg2);
void func_00194718(s32 arg0, s32 arg1);
void func_00194778(s32 arg0, s32 arg1);
void func_00193AC0(s32 arg0, s32 arg1, s32 arg2);

void func_001949F0(u8 *arg0) {
    u8 sp[0x10];
    u8 *s2;
    u8 *s4;
    u8 *s6;
    u8 *base170;
    u8 *base20;
    u8 *s1;
    u8 *s0l;

    s2 = *(u8 **)(arg0 + 0x38);
    s4 = s2 + 0x10;
    s6 = *(u8 **)(s4 + 0x38);
    if (func_001267E8(*(s32 *)(s4 + 0x40), *(u8 *)(s2 + 0x64)) != 0) {
        return;
    }
    if ((*(s32 *)(s2 + 0x60) & 0x40) && func_00126598(*(s32 *)(s4 + 0x40)) == 0) {
        return;
    }
    if (*(u8 *)(s6 + 1) == 1) {
        base20 = s2 + 0x20;
        base170 = s2 + 0x170;
        func_00129B58((s32)sp, gBtlCamView + 0x1F0, (s32)base20);
        *(f32 *)(sp + 0xC) = 1.0f;
        Vec3_Normalize((s32)sp, (s32)sp);
        *(f32 *)(s2 + 0x1B0) = Mathf_Asin(-*(f32 *)(sp + 4));
        *(f32 *)(s2 + 0x1B4) = atan2f(*(f32 *)sp, *(f32 *)(sp + 8));
        Mtx_RotateX(*(f32 *)(s2 + 0x1B0), (s32)base170, (s32)(s2 + 0x130));
        Mtx_RotateY(*(f32 *)(s2 + 0x1B4), (s32)base170, (s32)base170);
        for (s1 = *(u8 **)s2; s1 != NULL; s1 = *(u8 **)(s1 + 0x140)) {
            s0l = s1 + 0x90;
            Vec3_Add((s32)s0l, (s32)(s1 + 0x60), (s32)(s1 + 0x70));
            func_00129C50((s32)s0l, (s32)base170, (s32)s0l);
            Vec3_Add((s32)s0l, (s32)s0l, (s32)base20);
            func_00129C50((s32)(s1 + 0xE0), (s32)base170, (s32)(s1 + 0xC0));
            func_00129C50((s32)(s1 + 0xF0), (s32)base170, (s32)(s1 + 0xD0));
        }
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    switch (*(u8 *)(s6 + 3)) {
    case 0:
        func_00193470((s32)s2, (s32)s4, (s32)s6);
        break;
    case 1:
        func_00194718((s32)s2, (s32)s4);
        break;
    case 2:
        func_00194778((s32)s2, (s32)s4);
        break;
    case 3:
        func_00193AC0((s32)s2, (s32)s4, (s32)s6);
        break;
    }
    func_00128F08();
}
