#include "common.h"

extern f32 D_00384858;
extern f32 D_0038485C;
extern f32 D_00384860;
extern f32 D_00384864;
extern f32 D_00384868;
extern f32 D_0038486C;

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0016A488(void *arg0, void *arg1);
void func_0016A500(void *arg0, void *arg1, s32 arg2);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, void *arg1);
void func_00129C28(void *arg0, void *arg1);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Mtx_StoreIdentity(void *arg0);
void func_00128C58(f32 farg0, void *arg1, void *arg2);
void Mtx_RotateXYZ(void *arg0, void *arg1, void *arg2);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
f32 sinf(f32 farg0);

void func_0016A5A0(void *arg0) {
    u8 *s7;
    u8 *s3;
    u8 *fp;
    u8 *s1;
    u8 *s4;
    u8 *s5;
    u8 *s2;
    u8 *s0;
    u8 *v0p;
    s32 s6;
    s32 v1;
    s32 a0v;
    s32 nv0;
    s32 i;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;

    s7 = (u8 *)arg0;
    s3 = *(u8 **)(s7 + 0x38);
    fp = *(u8 **)(s3 + 0xB0);

    if (EftShot_TestBits(*(s32 *)fp, 2) != 0) {
        *(s32 *)(s3 + 0x4) = *(s32 *)(s3 + 0x4) | 9;
    } else if (EftShot_TestBits(*(s32 *)fp, 4) != 0) {
        *(s32 *)(s3 + 0x4) = *(s32 *)(s3 + 0x4) | 2;
    }
    if ((*(s32 *)s3 & 5) != 0) {
        *(s32 *)(s3 + 0x4) = *(s32 *)(s3 + 0x4) & -9;
    }
    if ((*(s32 *)(s3 + 0x4) & 1) == 0) {
        return;
    }

    s6 = 0;
    s4 = s3 + 0xAF0;
    s1 = s3 + 0xAB0;
    do {
        v1 = *(s32 *)(s1 + 0x34);
        if ((v1 & 1) == 0) {
            func_0016A488(s7, s1);
            *(s32 *)(s1 + 0x34) = *(s32 *)(s1 + 0x34) | 1;
            v1 = *(s32 *)(s1 + 0x34);
        }
        a0v = *(s32 *)(s3 + 0x4);

        if ((a0v & 8) != 0) {
            if ((v1 & 2) == 0) {
                func_001EDBD8(*(s32 *)(s1 + 0x30), 1);
                nv0 = *(s32 *)(s1 + 0x34) | 2;
                goto l6c8;
            }
            goto l6e4;
        }
        if ((v1 & 2) == 0) {
            s6 += 1;
            goto l83c;
        }
        func_001EDBD8(*(s32 *)(s1 + 0x30), 0);
        nv0 = *(s32 *)(s1 + 0x34) & -3;

    l6c8:
        *(s32 *)(s1 + 0x34) = nv0;
        v1 = *(s32 *)(s1 + 0x34);
        if ((v1 & 2) == 0) {
            s6 += 1;
            goto l83c;
        }
        a0v = *(s32 *)(s3 + 0x4);

    l6e4:
        if ((a0v & 2) == 0) {
            goto l728;
        }
        v1 = *(s32 *)(s1 + 0x34);
        if ((v1 & 4) == 0) {
            func_0016A500(s7, s1, s6);
            *(s32 *)(s1 + 0x34) = *(s32 *)(s1 + 0x34) | 4;
        }
        func_00129C28(s4, s3 + 0x80);
        s5 = s4;
        s2 = s1 + 0x50;
        goto l794;

    l728:
        func_00129C28(s4, s3 + 0x40);
        s5 = s4;
        if (*(s32 *)*(u8 **)(fp + 0x20) == 0x68) {
            f0 = sinf(*(f32 *)(s1 + 0x3C));
            f0 = f0 * 3.0f;
            f3 = D_00384858;
            f4 = *(f32 *)(s1 + 0x3C) + f3;
            f1 = *(f32 *)(s1 + 0x44) + f0;
            f2 = D_0038485C;
            *(f32 *)(s1 + 0x3C) = f4;
            *(f32 *)(s1 + 0x44) = f1;
            if (f2 <= f4) {
                f0 = D_00384860;
                *(f32 *)(s1 + 0x3C) = f4 - f0;
            }
        }
        s2 = s1 + 0x50;

    l794:
        Vec3_Add(s2, s2, s1 + 0x60);
        f3 = D_00384864;
        f1 = D_00384868;
        f2 = D_0038486C;
        v0p = s2;
        i = 2;
        do {
            f0 = *(f32 *)v0p;
            if (f3 < f0) {
                f0 = f0 - f1;
                *(f32 *)v0p = f0;
            } else if (f0 < f2) {
                f0 = f0 + f1;
                *(f32 *)v0p = f0;
            }
            i -= 1;
            v0p += 4;
        } while (i >= 0);

        s0 = s1 + 0x70;
        Mtx_StoreIdentity(s0);
        func_00128C58(*(f32 *)(s1 + 0x38), s0, s0);
        Mtx_RotateXYZ(s0, s0, s2);
        Mtx_Translate(s0, s0, s5);
        func_001EDD40(*(s32 *)(s1 + 0x30), s0);
        s6 += 1;

    l83c:
        s4 += 0xB0;
        s1 += 0xB0;
    } while (s6 <= 0);
}
