#include "common.h"

#define F32(p, off) (*(f32 *)((p) + (off)))

void func_00129C28(u8 *arg0, u8 *arg1);
s32 func_0020A440(s32 arg0);
void func_0012D5D8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 farg0, f32 farg1);
f32 Mathf_Asin(f32 farg0);
f32 EftMath_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void Mtx_StoreIdentity(u8 *arg0);
void func_00128C58(u8 *arg0, u8 *arg1, f32 farg0);
void Mtx_RotateZXY(u8 *arg0, u8 *arg1, u8 *arg2);
void Mtx_RotateY(u8 *arg0, u8 *arg1, f32 farg0);
void Mtx_RotateZ(u8 *arg0, u8 *arg1, f32 farg0);
void Mtx_RotateX(u8 *arg0, u8 *arg1, f32 farg0);
void Mtx_Translate(u8 *arg0, u8 *arg1, u8 *arg2);
void func_001EC310(u8 *arg0, u8 *arg1);
void func_00129D68(u8 *arg0, u8 *arg1, f32 farg0, f32 farg1);
extern f32 D_00384D6C;

void func_0019CCD8(u8 *arg0) {
    u8 sp[0x10];
    u8 *s1;
    u8 *s0;
    u8 *s2;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f20;
    s32 flags;
    s32 v;

    s1 = arg0;
    s0 = s1 + 0xA90;
    memset(sp, 0, 0x10);
    f2 = F32(s1, 0xC0C);
    f0 = F32(s0, 0);
    f4 = F32(s1, 0xC10);
    if (f2 < f0) {
        F32(s1, 0xBCC) = F32(s1, 0xBCC) + F32(s1, 0xBE4);
    }
    f3 = f2 / f4;
    f0 = F32(s1, 0xBE0);
    if (f0 <= f2) {
        if (f2 < f4) {
            F32(s1, 0xBCC) = F32(s1, 0xBCC) - F32(s1, 0xBE8);
        }
    }
    f0 = F32(s0, 0x8);
    if (f3 < f0) {
        F32(s1, 0xBEC) = F32(s1, 0xBEC) + F32(s1, 0xBF0);
    }
    f0 = F32(s0, 0x8);
    if (f0 <= f3) {
        f0 = 1.0f;
        if (f3 < f0) {
            F32(s1, 0xBEC) = F32(s1, 0xBEC) + F32(s1, 0xBF4);
        }
    }
    f20 = 0.0f;
    func_00129D68(s1 + 0xBC0, s1 + 0xBC0, f20, 255.0f);
    s2 = s1 + 0xB40;
    s0 = s1 + 0xB60;
    if (f20 < F32(s1, 0x34)) {
        v = func_0020A440(*(s32 *)(s1 + 0xC1C));
        if (v != 0) {
            func_0012D5D8(s0, s2, s0, *(s16 *)(s1 + 0x22), F32(s1, 0xBFC), F32(s1, 0x34));
            func_00129C28(sp, s0);
            f0 = Mathf_Asin(-F32(sp, 0x4));
            F32(s1, 0xC00) = EftMath_WrapAngle(f0);
            f0 = atan2f(F32(sp, 0x0), F32(sp, 0x8));
            F32(s1, 0xC04) = EftMath_WrapAngle(f0);
        }
    }
    s0 = s1 + 0xB60;
    f1 = F32(s1, 0xBFC);
    func_00129BD0(sp, s0, f1);
    flags = *(u16 *)(s1 + 0xC24);
    if (flags & 0x80) {
        func_00129C28(s1 + 0xB70, s1 + 0xB50);
        func_00129C28(s1 + 0xB50, s2);
    }
    s0 = s1 + 0xB80;
    func_00129B28(s2, s2, sp);
    Mtx_StoreIdentity(s0);
    func_00128C58(s0, s0, F32(s1, 0xBEC));
    func_00128C58(s0, s0, F32(s1, 0xBF8));
    Mtx_RotateZXY(s0, s0, s1 + 0xBD0);
    Mtx_RotateY(s0, s0, D_00384D6C);
    Mtx_RotateZ(s0, s0, F32(s1, 0xC08));
    Mtx_RotateX(s0, s0, F32(s1, 0xC00));
    Mtx_RotateY(s0, s0, F32(s1, 0xC04));
    flags = *(u16 *)(s1 + 0xC24);
    if ((flags & 0x2) == 0) {
        Mtx_Translate(s0, s0, s2);
    }
    func_001EC310(s1 + 0xAB0, s0);
    f0 = F32(s1, 0xC0C) + 1.0f;
    f2 = F32(s1, 0xC10);
    flags = (*(u16 *)(s1 + 0xC24) | 0x80);
    F32(s1, 0xC0C) = f0;
    if (f2 <= f0) {
        flags = flags | 0x4;
    }
    *(u16 *)(s1 + 0xC24) = (u16)flags;
}
