#include "common.h"

extern f32 D_00384F8C;
extern f32 D_00384F90;
extern f32 D_00384F94;
extern f32 D_00384F98;
extern f32 D_00384F9C;
extern f32 D_00384FA0;
extern f32 D_00384FA4;
extern f32 D_00384FA8;

s32 rand(void);
void func_001B0CD0(void *arg0, s32 arg1);
void func_001B0D88(void *arg0);
void func_001B0DF8(void *arg0, void *arg1);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateY(f32 farg0, void *arg1, void *arg2);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129BB8(f32 farg0, void *arg0, void *arg1);

s32 func_001B2090(u8 *arg0, u8 *arg1) {
    u8 sp[0x40];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    s32 r;
    s32 mode;
    s32 idx;
    s32 cnt;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f5;
    f32 f14;
    f32 f20;

    s5 = arg0;
    s1 = arg1;
    s4 = *(u8 **)(s5 + 0x38);
    s2 = *(u8 **)(s4 + 0x38);
    s0 = *(u8 **)(s4 + 0x3C);
    s3 = s1 + 0x90;

    *(s32 *)(s1 + 0) = 0;
    func_001B0CD0(s1, *(s32 *)(s4 + 0xA50));
    if (*(s32 *)(s1 + 4) < 3) {
        func_001B0D88(s1);
        return 0;
    }
    *(s32 *)(s1 + 8) = *(s32 *)(s1 + 8) | 1;

    r = rand();
    *(s32 *)(s1 + 0x10) = 0;
    f0 = (f32)r / D_00384F8C;
    f1 = *(f32 *)(s2 + 0x20);
    f2 = *(f32 *)(s2 + 0x1C);
    f1 = f1 * f0;
    f2 = f2 + f1;
    f2 = f2 * 30.0f;
    *(f32 *)(s1 + 0x14) = f2;
    *(f32 *)(s1 + 0x1C) = f2 * *(f32 *)(s2 + 0x24);
    *(f32 *)(s1 + 0x20) = f2 * *(f32 *)(s2 + 0x30);
    *(f32 *)(s1 + 0x24) = f2 - *(f32 *)(s2 + 0x70);
    f1 = *(f32 *)(s2 + 0x18);
    if (f1 <= *(f32 *)(s1 + 0x10)) {
        *(s32 *)(s1 + 8) = *(s32 *)(s1 + 8) | 4;
    } else {
        *(f32 *)(s1 + 0x18) = f2 - ((f32)*(s32 *)(s1 + 4) / f1);
    }

    *(s32 *)(s1 + 0xC) = 0;
    *(f32 *)(s1 + 0x3C) = 1.0f;
    f20 = D_00384F90;
    *(f32 *)(s1 + 0x38) = 1.0f;
    r = rand();
    *(f32 *)(s1 + 0x80) = *(f32 *)(s0 + 0x10) * ((f32)r / f20);
    r = rand();
    *(f32 *)(s1 + 0x84) = *(f32 *)(s0 + 0x14) * ((f32)r / f20);
    r = rand();
    *(f32 *)(s1 + 0x88) = *(f32 *)(s0 + 0x18) * ((f32)r / f20);
    Vec3_Add(s1 + 0x80, s1 + 0x80, s0);

    if (0.0f < *(f32 *)(s2 + 0x6C)) {
        *(f32 *)(s1 + 0x8C) = 0.0f;
    } else {
        r = rand();
        *(f32 *)(s1 + 0x8C) = *(f32 *)(s0 + 0xC) + *(f32 *)(s0 + 0x1C) * ((f32)r / f20);
    }

    *(s32 *)(s1 + 0x90) = 0;
    *(s32 *)(s1 + 0x94) = 0;
    *(s32 *)(s1 + 0x98) = 0;

    mode = *(u8 *)(s2 + 2);
    if (mode == 0 || (mode == 1 && (rand() & 1) == 0)) {
        /* the vector block at L22BC; a mode-1 test above consumed one rand() */
        s3 = s1 + 0x90;
        r = rand();
        f20 = D_00384F94;
        f1 = *(f32 *)(s0 + 0x30);
        *(f32 *)(s1 + 0x90) = f1 * ((f32)r / f20);
        r = rand();
        *(f32 *)(s1 + 0x94) = *(f32 *)(s0 + 0x34) * ((f32)r / f20);
        r = rand();
        *(f32 *)(s1 + 0x98) = *(f32 *)(s0 + 0x38) * ((f32)r / f20);
        Vec3_Add(s3, s3, s0 + 0x20);
        Vec3_Sub(s3, s3, s0);
        func_00129BD0(s3, s3, 1.0f / *(f32 *)(s1 + 0x14));
    }

    f0 = *(f32 *)(s2 + 0x6C);
    if (0.0f < f0) {
        r = rand();
        f0 = (f32)r / D_00384F98;
        f1 = *(f32 *)(s0 + 0x1C);
        f3 = *(f32 *)(s0 + 0xC);
        f2 = *(f32 *)(s2 + 0x6C);
        f1 = f1 * f0;
        f5 = f3 + f1;
        *(f32 *)(s1 + 0x9C) = f5 / f2;
    } else {
        *(f32 *)(s1 + 0x9C) = 0.0f;
    }

    idx = *(s32 *)(s4 + 0xA4C);
    *(f32 *)(s1 + 0x28) = *(f32 *)(s4 + 8 + (idx << 2) + 0xA60);
    idx = *(s32 *)(s4 + 0xA4C);
    *(f32 *)(s1 + 0x2C) = *(f32 *)(s4 + 8 + (idx << 2) + 0xA70);

    mode = *(u8 *)(s2 + 1);
    if (mode != 1) {
        *(s32 *)(s1 + 0x30) = 0;
        *(s32 *)(s1 + 0x34) = 0;
    } else if ((*(s32 *)(s4 + 0xA4C) & 1) == 0) {
        r = rand();
        f2 = *(f32 *)(s2 + 0x68);
        f0 = (f32)r / D_00384F9C;
        f3 = *(f32 *)(s2 + 0x64);
        f1 = (f32)*(s32 *)(s1 + 4);
        f5 = f3 + f2 * f0;
        *(f32 *)(s1 + 0x30) = f5 / f1;
        r = rand();
        f2 = *(f32 *)(s2 + 0x68);
        f0 = (f32)r / D_00384F9C;
        f3 = *(f32 *)(s2 + 0x64);
        f1 = (f32)*(s32 *)(s1 + 4);
        f5 = f3 + f2 * f0;
        *(f32 *)(s1 + 0x34) = f5 / f1;
    } else {
        r = rand();
        f1 = *(f32 *)(s2 + 0x68);
        f0 = (f32)r / D_00384FA0;
        f2 = *(f32 *)(s2 + 0x64);
        f3 = (f32)*(s32 *)(s1 + 4);
        f5 = f2 + f1 * f0;
        f0 = -f5;
        *(f32 *)(s1 + 0x30) = f0 / f3;
        r = rand();
        f1 = *(f32 *)(s2 + 0x68);
        f0 = (f32)r / D_00384FA0;
        f2 = *(f32 *)(s2 + 0x64);
        f3 = (f32)*(s32 *)(s1 + 4);
        f5 = f2 + f1 * f0;
        f0 = -f5;
        *(f32 *)(s1 + 0x34) = f0 / f3;
    }

    mode = *(u8 *)(s2 + 1);
    if (mode != 2) {
        Vec4_Set(s1 + 0x50, 0.0f, 0.0f, 0.0f, 1.0f);
    } else {
        s0 = s1 + 0x50;
        r = rand();
        f1 = *(f32 *)(s2 + 0x50);
        f14 = *(f32 *)(s2 + 0x4C);
        f0 = (f32)r / D_00384FA4;
        f1 = f1 - f14;
        f5 = f1 * f0;
        f14 = f5 + f14;
        Vec4_Set(s0, 0.0f, 0.0f, f14, 1.0f);
        Mtx_StoreIdentity(sp);
        Mtx_RotateY(*(f32 *)(s1 + 0x2C), sp, sp);
        func_00129C50(s0, sp, s0);
    }
    func_001B0DF8(s5, s1);

    s0 = s1 + 0x60;
    r = rand();
    f3 = (f32)r;
    f3 = f3 / D_00384FA8;
    f1 = *(f32 *)(s2 + 0x60);
    f5 = *(f32 *)(s2 + 0x5C);
    f1 = f1 * f3;
    f5 = f5 + f1;
    f2 = *(f32 *)(s1 + 0x30);
    f0 = *(f32 *)(s1 + 0x34);
    f2 = f2 * f5;
    *(f32 *)(s1 + 0x30) = f2;
    f0 = f0 * f5;
    *(f32 *)(s1 + 0x34) = f0;
    func_00129BD0(s0, s0, f5);
    func_00129BD0(s0, s0, 1.0f);
    func_00129BB8(1.0f, s3, s3);

    *(s32 *)(s4 + 0xA48) = *(s32 *)(s4 + 0xA48) + 1;
    return 1;
}
