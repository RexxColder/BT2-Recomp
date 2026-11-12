#include "common.h"

extern u8 *D_003878F4;
extern f32 D_003856B8;
extern f32 D_003856BC;

f32 BtlCharApi_GetHeight(s32 arg0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_001E7070(u8 *arg0);
s32 EftQuad_Create(u8 *arg0);
void func_0018E5E0(s32 arg0, s32 arg1);
s32 EftPtcl3_Create(u8 *arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void Vec4_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_001E70B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, u8 *t1, u8 *t2, s32 t3, f32 farg0);
void func_001E7208(u8 *arg0, s32 arg1);
s32 EftChain2_Create(u8 *arg0);
void EftChain2_SetType(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* Frame accessors: sw/lw as s32, lwc1/swc1 as f32, ld/sd as s64. */
#define W(o) (*(s32 *)(fr + (o)))
#define F(o) (*(f32 *)(fr + (o)))
#define D(o) (*(s64 *)(fr + (o)))

void func_001E7F30(u8 *arg0) {
    u8 fr[0x1D0] __attribute__((aligned(16)));
    u8 *s2;
    u8 *s3;
    u8 *s3b;
    u8 *s5;
    u8 *s0;
    u8 *s4;
    u8 *fp;
    u8 *s7p;
    u8 *p160;
    u8 *a0p;
    u8 *a1p;
    u8 *t0p;
    u8 *srcp;
    u8 *dstp;
    s32 s1;
    s32 s6;
    s32 s7;
    s32 v0;
    s32 r;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;
    f32 f21;

    s3 = D_003878F4 + 0x210;
    s2 = *(u8 **)(arg0 + 0x38);
    s5 = s2 + 0x68;
    p160 = *(u8 **)s3;
    W(0x160) = (s32)(s64)p160;

    /* Height, clamped below to D_003856BC. */
    f0 = BtlCharApi_GetHeight(*(s32 *)s5);
    f0 = f0 / D_003856B8;
    *(f32 *)(s2 + 0x60) = f0;
    if (f0 < D_003856BC) {
        *(f32 *)(s2 + 0x60) = D_003856BC;
    }

    W(0x164) = (s32)(s64)(s2 + 0x40);
    func_00208DE8(*(s32 *)s5, s2 + 0x40, 3);
    W(0x168) = (s32)(s64)(s2 + 0x50);
    func_00208DE8(*(s32 *)s5, s2 + 0x50, 0);

    s3b = s3 + (*(s32 *)(s2 + 0x64)) * 0x840 + 8;
    s0 = s2 + 0x88;
    s1 = 1;
    a0p = s2 + 0x88;
    do {
        s0 += 4;
        s1 -= 1;
        func_001E7070(a0p);
        a0p = s0;
    } while (s1 >= 0);

    /* Second loop (one pass: the back-edge tests the incremented index). */
    s1 = 0;
    f20 = 0.0f;
    f21 = 1.0f;
    fp = p160 + 4;
    s4 = s2 + 0x6C;
    s0 = p160 + 0x34;
    s6 = 0;
    v0 = *(s32 *)(s3b + 0x98);
    do {
        s1 += 1;
        v0 = v0 + s6;
        s6 += 0xB4;
        W(0x40) = v0;
        s7p = s3b + 8;
        W(0x48) = (s32)(s64)s7p;
        memset(fr + 0x50, 0, 0x10);
        W(0x44) = *(s32 *)(s3b + 0x9C) + ((s1 - 1) << 6);
        memset(fr + 0x60, 0, 0x10);

        f0 = *(f32 *)(s2 + 0x60);
        W(0x74) = 0;
        F(0x70) = f0;
        W(0x78) = *(s32 *)s5;

        /* 64-byte copy of the block at 0x40 down to 0x0 (and the 0x60 pair), then Vec4_Set into 0x20. */
        {
            s64 c60 = D(0x60);
            s64 t2 = D(0x40);
            s64 t1 = D(0x48);
            s64 v1r = D(0x50);
            s64 v0r = D(0x58);
            s64 a2r = D(0x68);
            s64 a3r = D(0x70);
            s64 t0r = D(0x78);
            D(0x20) = c60;
            D(0x0) = t2;
            D(0x8) = t1;
            D(0x10) = v1r;
            D(0x18) = v0r;
            D(0x28) = a2r;
            D(0x30) = a3r;
            D(0x38) = t0r;
        }
        Vec4_Set(fr + 0x20, f20, f21, f20, f21);

        func_00129C28(fr + 0x10, (u8 *)(s64)W(0x164));
        f1 = *(f32 *)s0;
        f2 = *(f32 *)(s2 + 0x60);
        f0 = F(0x14);
        s0 += 4;
        f1 = f1 * f2;
        f0 = f0 + f1;
        F(0x14) = f0;
        r = EftQuad_Create(fr);
        *(s32 *)s4 = r;
        s4 += 4;
        func_0018E5E0(r, 2);

        if (s1 <= 0) {
            v0 = *(s32 *)(s3b + 0x98);
        }
    } while (s1 <= 0);

    /* Third loop: three passes, index s1. */
    t0p = s3b + 0x1C8;
    W(0x16C) = (s32)(s64)t0p;
    s4 = fp + 0x20;
    f21 = f20;
    s1 = 0;
    fp = fr + 0x80;
    s0 = s2 + 0x74;
    s7 = 0;
    s6 = 0;
    W(0xD0) = 0;

    do {
        f0 = *(f32 *)(s2 + 0x60);
        memset(fr + 0xE0, 0, 0x10);
        F(0xD4) = f0;
        memset(fr + 0xF0, 0, 0x10);

        a0p = (u8 *)(s64)W(0x16C);
        W(0x100) = s1;
        W(0x104) = (s32)(s64)a0p;
        W(0x108) = *(s32 *)(s3b + 0x2D8) + s6;
        W(0x10C) = *(s32 *)(s3b + 0x2DC) + s7;
        W(0x110) = *(s32 *)s5;

        /* Copy fr+0xD0..0x10F to fp (two 32-byte chunks). */
        srcp = fr + 0xD0;
        dstp = fp;
        do {
            s64 x0 = *(s64 *)(srcp + 0x00);
            s64 x1 = *(s64 *)(srcp + 0x08);
            s64 x2 = *(s64 *)(srcp + 0x10);
            s64 x3 = *(s64 *)(srcp + 0x18);
            *(s64 *)(dstp + 0x00) = x0;
            *(s64 *)(dstp + 0x08) = x1;
            *(s64 *)(dstp + 0x10) = x2;
            *(s64 *)(dstp + 0x18) = x3;
            srcp += 0x20;
            dstp += 0x20;
        } while (srcp != fr + 0x110);

        t0p = fr + 0x90;
        a1p = (u8 *)(s64)W(0x168);
        *(s64 *)(fp + 0x40) = D(0x110);
        *(s64 *)(fp + 0x48) = D(0x118);
        s1 += 1;
        s7 += 0x50;
        func_00129C28(t0p, a1p);
        s6 += 0x164;

        f2 = *(f32 *)s4;
        f1 = *(f32 *)(s2 + 0x60);
        f0 = F(0x94);
        f2 = f2 * f1;
        s4 += 4;
        f0 = f0 + f2;
        a0p = fr + 0xA0;
        F(0x94) = f0;
        Vec4_Set(a0p, f21, -1.0f, f21, 1.0f);

        r = EftPtcl3_Create(fp);
        *(s32 *)s0 = r;
        s0 += 4;
        EftPtcl3_SetType(r, 2);

        if (s1 >= 3) {
            break;
        }
        W(0xD0) = 0;
    } while (1);

    /* Tail: ortho mtx and the chain/particle setup. */
    p160 = (u8 *)(s64)W(0x160);
    s0 = fr + 0x40;
    a1p = (u8 *)(s64)W(0x164);
    f0 = *(f32 *)(s2 + 0x60);
    a0p = s2 + 0x88;
    f20 = *(f32 *)(p160 + 0x40);
    f20 = f20 * f0;
    func_00129C28(s0, (u8 *)(s64)W(0x164));

    f2 = *(f32 *)(s2 + 0x60);
    f1 = *(f32 *)(p160 + 0x3C);
    f0 = F(0x44);
    f1 = f1 * f2;
    f0 = f0 + f1;
    F(0x44) = f0;
    {
        s32 t3 = *(s32 *)s5;
        func_001E70B0(a0p, *(s32 *)(s3b + 0x710), 0, 0, 0, fr + 0x40, s3b + 0x2E8, t3, f20);
    }
    func_001E7208(a0p, 2);

    v0 = *(s32 *)s5;
    F(0x128) = f21;
    W(0x124) = 0;
    W(0x120) = v0;
    f0 = *(f32 *)(s2 + 0x60);
    F(0x12C) = f0;
    memset(fr + 0x130, 0, 0x10);
    memset(fr + 0x140, 0, 0x10);

    W(0x154) = (s32)(s64)(s3b + 0x728);
    W(0x150) = 0;
    t0p = fr + 0xE0;
    {
        s64 t1;
        s64 v1r;
        s64 t3;
        s64 t2;
        s64 v0r;
        s64 t0r;
        s64 a2r;
        s64 a3r;
        t1 = D(0x130);
        v1r = D(0x140);
        W(0x158) = *(s32 *)(s3b + 0x838);
        W(0x15C) = *(s32 *)(s3b + 0x83C);
        t3 = D(0x120);
        t2 = D(0x128);
        v0r = D(0x148);
        t0r = D(0x138);
        a2r = D(0x150);
        a3r = D(0x158);
        D(0xE0) = t1;
        D(0xF0) = v1r;
        D(0xF8) = v0r;
        D(0xD0) = t3;
        D(0xD8) = t2;
        D(0xE8) = t0r;
        D(0x100) = a2r;
        D(0x108) = a3r;
    }
    func_00129C28(t0p, (u8 *)(s64)W(0x164));

    f2 = *(f32 *)(s2 + 0x60);
    f1 = *(f32 *)(p160 + 0x48);
    f0 = F(0xE4);
    f1 = f1 * f2;
    f0 = f0 + f1;
    F(0xE4) = f0;
    Vec4_Set(fr + 0xF0, f21, -1.0f, f21, 1.0f);

    r = EftChain2_Create(fr + 0xD0);
    *(s32 *)(s2 + 0x90) = r;
    EftChain2_SetType(r, 2);
}
