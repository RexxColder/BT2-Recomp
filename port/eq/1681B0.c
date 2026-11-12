#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))

void *func_001F3758(void *arg0);
void memset(void *arg0, s32 arg1, s32 arg2);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00129C38(void *arg0, void *arg1);
void func_001287A8(void *arg0, void *arg1);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateZXY(void *arg0, void *arg1, void *arg2);
void func_00128C28(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
void func_001EDD40(s32 arg0, void *arg1);
s32 func_0020B3D0(s32 arg0);

void func_001681B0(u8 *arg0) {
    u8 sp[0xb0];   /* tamano de locales del original (antes 0xa8) */
    u8 *fp;
    u8 *ps;
    u8 *s0;
    u8 *s2;
    u8 *s6;
    u8 *s7;
    u8 *spA0;
    s32 spA4;
    s32 s1;
    s32 r1;
    s32 r2;
    s32 v1;
    u8 *tb;
    u8 *v0p;

    v0p = (u8 *)func_001F3758(arg0);
    fp = *(u8 **)(arg0 + 0x38);
    ps = *(u8 **)(fp + 0x120);
    spA4 = 0;
    spA0 = *(u8 **)(v0p + 0x38);
    memset(sp, 0, 0x40);
    s1 = W(ps, 0);

    if (EftShot_TestBits(W(ps, 0), 0x40) != 0) {
        v1 = W(fp, 4);
        if (v1 & 8) {
            W(fp, 4) = v1 | 0x10;
        }
    }
    if (EftShot_TestBits(W(ps, 0), 0x40) != 0) {
        func_001EDBD8(W(fp, 8), 1);
        W(fp, 4) = W(fp, 4) | 9;
    }
    if (W(fp, 0) & 5) {
        func_001EDBD8(W(fp, 8), 0);
        W(fp, 4) = W(fp, 4) | 4;
    }

    s7 = fp + 0x70;
    if (W(fp, 4) & 8) {
        s1 = W(ps, 0);
        spA4 = 0;
        func_00208DE8(s1, s7, 0x1F);
    }
    if ((W(fp, 0) & 0x200) && (W(fp, 4) & 0x10)) {
        spA4 = 1;
        r1 = func_0020B3D0(W(ps, 0));
        r2 = func_0020B3D0(W(ps, 0));
        s1 = r1;
        func_00208DE8(r2, s7, 0x1F);
    }

    s0 = sp + 0x50;
    Vec4_Set(s0, 0.0f, -1.0f, 0.0f, 1.0f);
    s6 = fp + 0x80;
    s2 = fp + 0x30;
    Vec4_Set(sp + 0x90, 1.0f, 1.0f, 1.0f, 1.0f);

    func_00208DE8(s1, sp + 0x70, 0x15);
    func_00208DE8(s1, sp + 0x80, 0x19);
    Vec3_Sub(sp + 0x60, sp + 0x80, sp + 0x70);
    func_00208DE8(s1, sp + 0x80, 0x1F);
    Vec3_Sub(sp + 0x40, sp + 0x80, sp + 0x70);
    Vec3_Cross(s0, sp + 0x60, sp + 0x40);
    Vec3_Cross(sp + 0x40, sp + 0x60, s0);
    Vec3_Normalize(sp + 0x40, sp + 0x40);
    Vec3_Normalize(s0, s0);
    Vec3_Normalize(sp + 0x60, sp + 0x60);

    func_00129C38(sp, sp + 0x40);
    func_00129C38(sp + 0x10, s0);
    func_00129C38(sp + 0x20, sp + 0x60);
    func_001287A8(s6, sp);
    Mtx_StoreIdentity(s2);
    Mtx_RotateZXY(s2, s2, s6);
    func_00128C28(s2, s2, sp + 0x90);

    tb = spA0 + (spA4 * 4) + 0x1E80;
    func_00129BD0(sp + 0x70, sp + 0x40, FL(tb, 4));
    func_00129BD0(sp + 0x80, sp + 0x60, FL(tb, 0xC));
    Mtx_Translate(s2, s2, sp + 0x70);
    Mtx_Translate(s2, s2, sp + 0x80);
    Mtx_Translate(s2, s2, s7);
    func_001EDD40(W(fp, 8), s2);
}
