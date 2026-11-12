#include "common.h"

extern f32 D_00384778;
extern f32 D_0038477C;
extern f32 D_00384780;
extern f32 D_00384784;
extern f32 D_00384788;

s32 BtlCharApi_IsHidden(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void EftStruggle_SetPos(u8 *arg0);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00162F98(s32 arg0, u8 *arg1, u8 *arg2);
void func_00163710(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
void func_001A7A50(u8 *arg0);
void func_001A7AC8(void);
void func_001F45C0(f32 farg0);
void func_001F45D8(u8 *arg0);
s32 func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);

void func_00163BD8(u8 *arg0) {
    u8 sp[0x10];
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s0;
    u8 *s4;
    s32 v;
    s32 a2;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;

    s1 = *(u8 **)(arg0 + 0x38);
    *(s32 *)(s1 + 0xAB4) = *(s32 *)(s1 + 0xAB4) + 1;
    s2 = s1 + 0x50;
    s4 = *(u8 **)(s1 + 0xB0);
    s0 = s1 + 0xA0;
    s3 = s1 + 0x80;
    a2 = *(s32 *)(s1 + 0x8);
    func_00208DE8(*(s32 *)s4, s2, a2);
    Vec3_Normalize(s0, s0);
    func_00129BD0(s0, s0, 3.5f);
    Vec3_Add(s2, s2, s0);
    Vec3_Normalize(s0, s0);
    func_00129BD0(s0, s0, 60.0f);
    Vec3_Add(s3, s2, s0);
    if (BtlCharApi_IsHidden(*(s32 *)s4) != 0) {
        f0 = *(f32 *)(s1 + 0x54) + 200.0f;
        f1 = *(f32 *)(s1 + 0x84) + 200.0f;
        *(f32 *)(s1 + 0x54) = f0;
        *(f32 *)(s1 + 0x84) = f1;
    }
    func_00162F98(*(s32 *)s4, s1 + 0x860, s2);
    if (*(s32 *)(s1 + 0xAB4) == 0x32) {
        func_001A7A50(s3);
    }
    EftStruggle_SetPos(s3);
    v = *(s32 *)(s1 + 0xAB4);
    if (v % 3 == 0) {
        func_00208DE8(*(s32 *)s4, sp, 3);
        f22 = D_00384778;
        f23 = 5.0f;
        f24 = D_0038477C;
        f21 = 4.0f;
        f20 = D_00384780;
        func_00163710(sp, f22, f23, 45.0f, f24, f21, f20);
        func_00163710(sp, f22, f23, 15.0f, f24, f21, f20);
    }
    if (EftShot_TestBits(*(s32 *)s4, 0x10) != 0) {
        v = *(s32 *)s1;
        if (v & 0x200) {
            v = v & 0xFFFFFDFF;
        } else {
            v = v | 0x200;
        }
        *(s32 *)s1 = v;
    }
    v = *(s32 *)s1;
    if ((v & 0x200) == 0) {
        f1 = *(f32 *)(s1 + 0x20);
        f1 = f1 * 0.5f;
        f0 = *(f32 *)(s1 + 0x14);
        f1 = f1 + 1.0f;
        f0 = f0 * f1;
        *(f32 *)(s1 + 0x18) = f0;
    } else {
        *(f32 *)(s1 + 0x18) = D_00384784;
    }
    v = *(s32 *)(s1 + 0xAB4);
    if (v >= 0x3F0) {
        f0 = *(f32 *)(s1 + 0xAB0) + D_00384788;
        *(f32 *)(s1 + 0xAB0) = f0;
        if (1.0f < f0) {
            *(f32 *)(s1 + 0xAB0) = 1.0f;
        }
    }
    if (v == 0x43C) {
        *(s32 *)(s1 + 0xAB0) = 0;
        func_001A7AC8();
        *(s32 *)s1 = *(s32 *)s1 | 0x400;
    }
    func_001F45C0(*(f32 *)(s1 + 0xAB0));
    func_001F45D8(s1 + 0x30);
}
