#include "common.h"

extern u8 *gEftStruggle;

void *memset(void *arg0, s32 arg1, u32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
s32 func_00126560(void);
void func_001E7070(s32 arg0);
s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_00129C28(s32 arg0, s32 arg1);
s32 EftQuad_Create(s32 arg0);
void func_0018E5E0(s32 arg0, s32 arg1);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
s32 func_001A83D8(s32 arg0);
s32 func_001E70B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0);
void func_001E7208(s32 arg0, s32 arg1);
s32 EftChain2_Create(s32 arg0);
void EftChain2_SetType(s32 arg0, s32 arg1);
s32 func_001CC978(s32 arg0);
void func_001CCD10(s32 arg0, s32 arg1);

void func_001A8418(u8 *arg0) {
    s64 fr[0x1B8 / 8];
    u8 *sp = (u8 *)fr;
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    u8 *fp;
    u8 *s1p;
    s32 s1;
    s32 s4;
    s32 v0;
    s32 v1;
    s32 i;
    s32 vA;
    s64 t0v, t1v, t2v, t3v, v0v, v1v, a2v, a3v;
    f32 f0;
    f32 f20;
    f32 f21;

    s3 = gEftStruggle + 8;
    *(s32 *)(sp + 0x1A0) = (s32)arg0;
    s2 = *(u8 **)(arg0 + 0x38);
    *(s32 *)(sp + 0x1A8) = (s32)(s2 + 0x10);
    s7 = s2 + 0x60;
    *(s32 *)(sp + 0x1A4) = *(s32 *)s3;
    Vec3_Sub((s32)(s2 + 0x10), (s32)(s2 + 0x1F0), (s32)(s2 + 0x70));
    Vec3_Normalize(*(s32 *)(sp + 0x1A8), *(s32 *)(sp + 0x1A8));
    *(f32 *)(s2 + 0x30) = 1.0f;
    v0 = func_00126560();
    if (v0 != 0) {
        *(f32 *)(s2 + 0x30) = 1.5f;
    }
    v1 = *(s32 *)(s2 + 0x2C);
    s0 = s2 + 0x374;
    s1 = 3;
    v0 = ((v1 * 49) << 5);
    s3 = s3 + v0;
    s3 = s3 + 8;
    s1p = s0;
    for (;;) {
        s0 += 4;
        s1 -= 1;
        func_001E7070((s32)s1p);
        s1p = s0;
        if (s1 < 0) {
            break;
        }
    }

    f20 = 0.0f;
    s1 = 0;
    f21 = 1.0f;
    s5 = s3 + 8;
    fp = sp + 0x20;
    s6 = sp + 0x10;
    s0 = s2 + 0x360;
    s4 = 0;
    v0 = *(s32 *)(s3 + 0x98);

    /* loop A: one pass (the blezl sees s1 after the increment) */
    v1 = s1 << 6;
    s1 += 1;
    vA = v0 + s4;
    s4 += 0xB4;
    *(s32 *)(sp + 0x40) = vA;
    *(s32 *)(sp + 0x48) = (s32)s5;
    memset(sp + 0x50, 0, 0x10);
    *(s32 *)(sp + 0x44) = *(s32 *)(s3 + 0x9C) + v1;
    memset(sp + 0x60, 0, 0x10);
    *(f32 *)(sp + 0x70) = *(f32 *)(s2 + 0x30);
    *(s32 *)(sp + 0x74) = 0;
    *(s32 *)(sp + 0x78) = *(s32 *)s7;
    for (i = 0; i < 8; i++) {
        fr[i] = fr[i + 8];
    }
    Vec4_Set((s32)fp, f20, f21, f20, f21);
    func_00129C28((s32)s6, (s32)s2);
    v0 = EftQuad_Create((s32)sp);
    *(s32 *)s0 = v0;
    s0 += 4;
    func_0018E5E0(v0, 2);

    f21 = f20;
    s1 = 0;
    fp = s3 + 0xA8;
    s6 = sp + 0x80;
    s0 = s2 + 0x364;
    s4 = 0;
    s5 = 0;
    *(s32 *)(sp + 0xD0) = 0;

    /* loop B: four passes */
    do {
        memset(sp + 0xE0, 0, 0x10);
        *(f32 *)(sp + 0xD4) = *(f32 *)(s2 + 0x30);
        memset(sp + 0xF0, 0, 0x10);
        *(s32 *)(sp + 0x100) = s1;
        *(s32 *)(sp + 0x104) = (s32)fp;
        *(s32 *)(sp + 0x108) = *(s32 *)(s3 + 0x1B8) + s4;
        *(s32 *)(sp + 0x10C) = *(s32 *)(s3 + 0x1BC) + s5;
        *(s32 *)(sp + 0x110) = *(s32 *)s7;
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
        s5 += 0x50;
        func_00129C28(sp + 0x90, (s32)s2);
        s4 += 0x164;
        Vec4_Set((s32)(sp + 0xA0), f21, -1.0f, f21, 1.0f);
        v0 = EftPtcl3_Create((s32)s6);
        *(s32 *)s0 = v0;
        s0 += 4;
        EftPtcl3_SetType(v0, 2);
        if (s1 < 4) {
            *(s32 *)(sp + 0xD0) = 0;
            continue;
        }
        break;
    } while (1);

    v0 = func_001A83D8(*(s32 *)(sp + 0x1A0));
    f0 = *(f32 *)(s2 + 0x30);
    s0 = s2 + (v0 << 2);
    f20 = *(f32 *)(*(u8 **)(sp + 0x1A4));
    s1p = sp + 0x40;
    s0 += 0x374;
    f20 = f20 * f0;
    func_00129C28((s32)s1p, (s32)s2);
    func_001E70B0((s32)s0, *(s32 *)(s3 + 0x3D8), 0, 0, 0, (s32)s1p, (s32)(s3 + 0x1C8), 0, f20);
    func_001E7208((s32)s0, 2);

    *(f32 *)(sp + 0x128) = f21;
    *(s32 *)(sp + 0x120) = 0;
    *(s32 *)(sp + 0x124) = 0;
    s0 = sp + 0x130;
    memset(sp + 0x130, 0, 0x10);
    *(f32 *)(sp + 0x12C) = *(f32 *)(s2 + 0x30);
    memset(sp + 0x140, 0, 0x10);
    *(s32 *)(sp + 0x154) = (s32)(s3 + 0x3E8);
    *(s32 *)(sp + 0x150) = 0;
    *(s32 *)(sp + 0x158) = *(s32 *)(s3 + 0x4F8);
    *(s32 *)(sp + 0x15C) = *(s32 *)(s3 + 0x4FC);
    t3v = fr[0x120 / 8];
    t2v = fr[0x128 / 8];
    t1v = fr[0x130 / 8];
    t0v = fr[0x138 / 8];
    v1v = fr[0x140 / 8];
    v0v = fr[0x148 / 8];
    a2v = fr[0x150 / 8];
    a3v = fr[0x158 / 8];
    fr[0xD0 / 8] = t3v;
    fr[0xD8 / 8] = t2v;
    fr[0xE0 / 8] = t1v;
    fr[0xE8 / 8] = t0v;
    fr[0xF0 / 8] = v1v;
    fr[0xF8 / 8] = v0v;
    fr[0x100 / 8] = a2v;
    fr[0x108 / 8] = a3v;
    func_00129C28(sp + 0xE0, (s32)s2);
    Vec4_Set((s32)(sp + 0xF0), f21, -1.0f, f21, 1.0f);
    v0 = EftChain2_Create((s32)(sp + 0xD0));
    *(s32 *)(s2 + 0x384) = v0;
    EftChain2_SetType(v0, 2);

    *(f32 *)(sp + 0x168) = f21;
    *(s32 *)(sp + 0x160) = 0;
    *(s32 *)(sp + 0x164) = 0;
    memset(sp + 0x170, 0, 0x10);
    *(f32 *)(sp + 0x16C) = *(f32 *)(s2 + 0x30);
    memset(sp + 0x180, 0, 0x10);
    *(s32 *)(sp + 0x190) = (s32)(s3 + 0x508);
    *(s32 *)(sp + 0x194) = *(s32 *)(s3 + 0x618);
    *(s32 *)(sp + 0x198) = *(s32 *)(s3 + 0x61C);
    t0v = fr[0x178 / 8];
    t3v = fr[0x160 / 8];
    t2v = fr[0x168 / 8];
    t1v = fr[0x170 / 8];
    v1v = fr[0x180 / 8];
    v0v = fr[0x188 / 8];
    a2v = fr[0x190 / 8];
    a3v = fr[0x198 / 8];
    fr[0x128 / 8] = t0v;
    fr[0x110 / 8] = t3v;
    fr[0x118 / 8] = t2v;
    fr[0x120 / 8] = t1v;
    fr[0x130 / 8] = v1v;
    fr[0x138 / 8] = v0v;
    fr[0x140 / 8] = a2v;
    fr[0x148 / 8] = a3v;
    func_00129C28(sp + 0x120, (s32)(s2 + 0x10));
    func_00129C28((s32)s0, (s32)(s2 + 0x10));
    v0 = func_001CC978((s32)(sp + 0x110));
    *(s32 *)(s2 + 0x388) = v0;
    func_001CCD10(v0, 2);
}
