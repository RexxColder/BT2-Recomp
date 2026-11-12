#include "common.h"

extern u8 *D_00387840;
extern f32 D_00384ED4;

void *memset(void *arg0, s32 arg1, u32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_001E7070(s32 arg0);
s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_00129C28(s32 arg0, s32 arg1);
s32 EftQuad_Create(s32 arg0);
void func_0018E5E0(s32 arg0, s32 arg1);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
s32 func_001E70B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0);
void func_001E7208(s32 arg0, s32 arg1);
s32 EftChain2_Create(s32 arg0);
void EftChain2_SetType(s32 arg0, s32 arg1);

void func_001A9178(u8 *arg0, u8 *arg1) {
    s64 fr[0x170 / 8];
    u8 *sp = (u8 *)fr;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s6;
    u8 *s7;
    u8 *s0p;
    u8 *s1p;
    s32 s0i;
    s32 s1;
    s32 s5;
    s32 s6i;
    s32 v0;
    s32 v1;
    s32 p;
    s32 i;
    s64 t[8];
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;
    f32 f21;
    f32 h;

    s3 = D_00387840 + 8;
    s2 = *(u8 **)(arg0 + 0x38);
    *(s32 *)(sp + 0x160) = *(s32 *)s3;
    memset(s2, 0, 0x60);
    v1 = *(s32 *)arg1;
    *(s32 *)(s2 + 8) = 1;
    *(s32 *)s2 = v1;
    h = BtlCharApi_GetHeight(v1);
    f0 = h / D_00384ED4;
    *(f32 *)(s2 + 0xC) = f0;
    if (f0 < 0.5f) {
        *(f32 *)(s2 + 0xC) = 0.5f;
    }
    s7 = s2 + 0x10;
    func_00208DE8(*(s32 *)s2, (s32)s7, 3);
    func_00208DE8(*(s32 *)s2, (s32)(s2 + 0x20), 0);

    v1 = *(s32 *)(s2 + 8);
    s1 = 1;
    s3 = s3 + (v1 * 33 << 6);
    s3 = s3 + 8;
    s1p = s2 + 0x4C;
    s0p = s1p;
    for (;;) {
        s0p += 4;
        s1 -= 1;
        func_001E7070((s32)s1p);
        s1p = s0p;
        if (s1 < 0) {
            break;
        }
    }

    p = *(s32 *)(sp + 0x160);
    s1 = 0;
    f20 = 0.0f;
    s6 = s3 + 8;
    f21 = 1.0f;
    s4 = (u8 *)(p + 4);
    s0i = 0x30;
    s5 = 0;
    v0 = *(s32 *)(s3 + 0x98);

    /* loop A: one pass (blezl on s1 after the increment) */
    {
        s32 v0a;
        v1 = s1 << 6;
        s1 += 1;
        v0a = v0 + s5;
        s5 += 0xB4;
        *(s32 *)(sp + 0x40) = v0a;
        *(s32 *)(sp + 0x48) = (s32)s6;
        memset(sp + 0x50, 0, 0x10);
        *(s32 *)(sp + 0x44) = *(s32 *)(s3 + 0x9C) + v1;
        memset(sp + 0x60, 0, 0x10);
        *(f32 *)(sp + 0x70) = *(f32 *)(s2 + 0xC);
        *(s32 *)(sp + 0x74) = 0;
        *(s32 *)(sp + 0x78) = *(s32 *)arg1;
        for (i = 0; i < 8; i++) {
            fr[i] = fr[i + 8];
        }
        Vec4_Set((s32)(sp + 0x20), f20, f21, f20, f21);
        func_00129C28((s32)(sp + 0x10), (s32)s7);
        f1 = *(f32 *)(s4 + s0i);
        f2 = *(f32 *)(s2 + 0xC);
        f0 = *(f32 *)(sp + 0x14);
        f1 = f1 * f2;
        f0 = f0 + f1;
        *(f32 *)(sp + 0x14) = f0;
        v0 = EftQuad_Create((s32)sp);
        *(s32 *)(s2 + s0i) = v0;
        s0i += 4;
        func_0018E5E0(v0, 2);
    }

    f21 = f20;
    *(s32 *)(sp + 0x164) = (s32)(s3 + 0x1C8);
    s4 += 0x20;
    s1 = 0;
    s0p = s2 + 0x38;
    s6i = 0;
    s5 = 0;
    *(s32 *)(sp + 0xD0) = 0;

    /* loop B: three passes */
    do {
        memset(sp + 0xE0, 0, 0x10);
        *(f32 *)(sp + 0xD4) = *(f32 *)(s2 + 0xC);
        memset(sp + 0xF0, 0, 0x10);
        v1 = *(s32 *)arg1;
        v0 = *(s32 *)(sp + 0x164);
        *(s32 *)(sp + 0x100) = s1;
        *(s32 *)(sp + 0x104) = v0;
        *(s32 *)(sp + 0x108) = *(s32 *)(s3 + 0x2D8) + s5;
        *(s32 *)(sp + 0x10C) = *(s32 *)(s3 + 0x2DC) + s6i;
        *(s32 *)(sp + 0x110) = v1;
        {
            s32 d2 = 0xD0;
            s32 d3 = 0x80;
            do {
                fr[(d3 / 8)] = fr[(d2 / 8)];
                fr[(d3 / 8) + 1] = fr[(d2 / 8) + 1];
                fr[(d3 / 8) + 2] = fr[(d2 / 8) + 2];
                fr[(d3 / 8) + 3] = fr[(d2 / 8) + 3];
                d2 += 0x20;
                d3 += 0x20;
            } while (d2 != 0x110);
            fr[0xC0 / 8] = fr[0x110 / 8];
            fr[0xC8 / 8] = fr[0x118 / 8];
        }
        s1 += 1;
        s6i += 0x50;
        s5 += 0x164;
        func_00129C28((s32)(sp + 0x90), (s32)s7);
        f2 = *(f32 *)s4;
        f1 = *(f32 *)(s2 + 0xC);
        f0 = *(f32 *)(sp + 0x94);
        f2 = f2 * f1;
        s4 += 4;
        f0 = f0 + f2;
        *(f32 *)(sp + 0x94) = f0;
        Vec4_Set((s32)(sp + 0xA0), f21, -1.0f, f21, 1.0f);
        v0 = EftPtcl3_Create((s32)(sp + 0x80));
        *(s32 *)s0p = v0;
        s0p += 4;
        EftPtcl3_SetType(v0, 2);
        if (s1 < 3) {
            *(s32 *)(sp + 0xD0) = 0;
            continue;
        }
        break;
    } while (1);

    p = *(s32 *)(sp + 0x160);
    s0p = sp + 0x40;
    f0 = *(f32 *)(s2 + 0xC);
    f20 = *(f32 *)(p + 0x40);
    s1p = s2 + 0x4C;
    f20 = f20 * f0;
    func_00129C28((s32)(sp + 0x40), (s32)s7);

    v0 = *(s32 *)(sp + 0x160);
    f2 = *(f32 *)(s2 + 0xC);
    f1 = *(f32 *)(v0 + 0x3C);
    f0 = *(f32 *)(sp + 0x44);
    f1 = f1 * f2;
    f0 = f0 + f1;
    *(f32 *)(sp + 0x44) = f0;
    func_001E70B0((s32)s1p, *(s32 *)(s3 + 0x710), 0, 0, 0, (s32)(sp + 0x40), (s32)(s3 + 0x2E8), *(s32 *)arg1, f20);
    func_001E7208((s32)s1p, 2);

    v1 = *(s32 *)(s2 + 8);
    if (v1 == 1) {
        v0 = *(s32 *)arg1;
        *(s32 *)(sp + 0x124) = 0;
        *(s32 *)(sp + 0x120) = v0;
        *(f32 *)(sp + 0x128) = f21;
        *(f32 *)(sp + 0x12C) = *(f32 *)(s2 + 0xC);
        memset(sp + 0x130, 0, 0x10);
        memset(sp + 0x140, 0, 0x10);
        *(s32 *)(sp + 0x154) = (s32)(s3 + 0x728);
        *(s32 *)(sp + 0x150) = 0;
        t[0] = fr[0x138 / 8];
        v0 = *(s32 *)(s3 + 0x838);
        *(s32 *)(sp + 0x158) = v0;
        t[1] = fr[0x120 / 8];
        t[2] = fr[0x128 / 8];
        v0 = *(s32 *)(s3 + 0x83C);
        *(s32 *)(sp + 0x15C) = v0;
        t[3] = fr[0x130 / 8];
        t[4] = fr[0x140 / 8];
        t[5] = fr[0x148 / 8];
        t[6] = fr[0x150 / 8];
        t[7] = fr[0x158 / 8];
        fr[0xE8 / 8] = t[0];
        fr[0xD0 / 8] = t[1];
        fr[0xD8 / 8] = t[2];
        fr[0xE0 / 8] = t[3];
        fr[0xF0 / 8] = t[4];
        fr[0xF8 / 8] = t[5];
        fr[0x100 / 8] = t[6];
        fr[0x108 / 8] = t[7];
        func_00129C28((s32)(sp + 0xE0), (s32)s7);
        f2 = *(f32 *)(s2 + 0xC);
        f1 = *(f32 *)(*(u8 **)(sp + 0x160) + 0x48);
        f0 = *(f32 *)(sp + 0xE4);
        f1 = f1 * f2;
        f0 = f0 + f1;
        *(f32 *)(sp + 0xE4) = f0;
        Vec4_Set((s32)(sp + 0xF0), f21, -1.0f, f21, 1.0f);
        v0 = EftChain2_Create((s32)(sp + 0xD0));
        *(s32 *)(s2 + 0x54) = v0;
        EftChain2_SetType(v0, 2);
    }

    *(s16 *)(D_00387840 + 0x1090) = 0;
}
