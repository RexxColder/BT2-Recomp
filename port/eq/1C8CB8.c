#include "common.h"

extern f32 D_003851A4;

void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Mtx_StoreIdentity(s32 arg0);
void func_00129C38(s32 arg0, s32 arg1);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);

void func_001C8CB8(u8 *arg0) {
    u8 sp[0x70];   /* tamano de locales del original (antes 0x60) */
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    u8 *fp;
    u8 *s1;
    u8 *v;
    f32 f20;

    f20 = D_003851A4;
    s0 = *(u8 **)(arg0 + 0x38);
    s2 = s0 + 0x30;
    s7 = *(u8 **)s0;
    s3 = s0 + 0x40;
    func_00208DE8(*(s32 *)(s0 + 0x90), (s32)sp, 0x21);
    s4 = sp + 0x10;
    func_00208DE8(*(s32 *)(s0 + 0x90), (s32)s4, 0x13);
    fp = s0 + 0x50;
    Vec3_Sub((s32)s2, (s32)s4, (s32)sp);
    Vec3_Normalize((s32)s2, (s32)s2);
    s6 = s0 + 0x60;
    func_00208DE8(*(s32 *)(s0 + 0x90), (s32)sp, 0x38);
    func_00208DE8(*(s32 *)(s0 + 0x90), (s32)s4, 0x37);
    Vec3_Sub((s32)s3, (s32)s4, (s32)sp);
    Vec3_Normalize((s32)s3, (s32)s3);
    s5 = s0 + 0x70;
    Vec3_Cross((s32)fp, (s32)s2, (s32)s3);
    Vec3_Cross((s32)s3, (s32)s2, (s32)fp);

    s1 = sp + 0x30;
    Mtx_StoreIdentity((s32)s1);
    func_00129C38((s32)s1, (s32)s2);
    func_00129C38((s32)(sp + 0x40), (s32)s3);
    func_00129C38((s32)(sp + 0x50), (s32)fp);

    *(s32 *)(s0 + 0x80) = 0;
    *(f32 *)(s0 + 0x84) = cosf(*(f32 *)(s7 + 0x2C) * f20);
    *(s32 *)(s0 + 0x8C) = 0;
    *(f32 *)(s0 + 0x88) = sinf(*(f32 *)(s7 + 0x2C) * f20);

    func_00129C50((s32)(s0 + 0x80), (s32)s1, (s32)(s0 + 0x80));
    func_00129C28((s32)s6, (s32)s4);
    func_00129C28((s32)s5, (s32)s4);

    v = sp + 0x20;
    func_00129BD0((s32)v, (s32)s2, *(f32 *)(s7 + 0x20));
    Vec3_Add((s32)s6, (s32)s6, (s32)v);
    func_00129BD0((s32)v, (s32)v, -1.0f);
    Vec3_Add((s32)s5, (s32)s5, (s32)v);
    func_00129BD0((s32)v, (s32)s3, *(f32 *)(s7 + 0x24));
    Vec3_Add((s32)s6, (s32)s6, (s32)v);
    Vec3_Add((s32)s5, (s32)s5, (s32)v);
    func_00129BD0((s32)v, (s32)fp, *(f32 *)(s7 + 0x28));
    Vec3_Add((s32)s6, (s32)s6, (s32)v);
    Vec3_Add((s32)s5, (s32)s5, (s32)v);
}
