#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define FLDU16(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define FLD64(p, off) (*(s64 *)((u8 *)(p) + (off)))

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern s32 gBtlCamView;

void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
s32 func_001294B0(void *arg0, void *arg1, s32 arg2, s32 arg3);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C28(void *arg0, s32 arg1);
void func_00129D40(void *arg0, void *arg1, s32 arg2, s32 arg3);

/* packs a 24-bit value into bits 32..55 of the s64 at p+0x40 (or +0x58, +0x70, +0x88) */
#define PACK_COL(p, off, w) do { \
        s64 _v = FLD64(p, off); \
        _v = (_v & 0xFF000000FFFFFFFFLL) | ((s64)((w) & 0xFFFFFF) << 32); \
        FLD64(p, off) = _v; \
        ((u8 *)(p))[(off) + 7] = 0xFF; \
    } while (0)

void func_001CC0A0(void *arg0) {
    u8 spb[0x1C0];
    u8 *sp = spb;
    u8 *E = (u8 *)arg0;
    u8 *T;
    u8 *s0;
    u8 *s1p;
    u8 *s2;
    u8 *s4;
    u8 *e1;
    u8 *sp150;
    s32 s1;
    s32 a0b;
    s32 a1;
    s32 v1;
    s32 k16;
    s32 X;
    s32 total;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f12;

    T = (u8 *)FLD(E, 0x38);
    s2 = T + 0x10;
    s4 = T + 0x20;
    sp150 = (u8 *)FLD(T, 0x34);
    func_00129C28(sp + 0xC0, gBtlCamView + 0x1F0);
    Vec3_Sub(sp + 0xD0, s2, sp + 0xC0);
    Vec3_Cross(sp + 0xD0, s4, sp + 0xD0);
    Vec3_Normalize(sp + 0xD0, sp + 0xD0);
    func_00129BD0(sp + 0xE0, sp + 0xD0, FLDF(T, 0x64));
    Vec3_Add(sp, s2, sp + 0xE0);
    Vec3_Sub(sp + 0x10, s2, sp + 0xE0);
    func_00129BD0(sp + 0xF0, s4, FLDF(T, 0x68));
    Vec3_Add(sp + 0x20, sp, sp + 0xF0);
    Vec3_Add(sp + 0x30, sp + 0x10, sp + 0xF0);
    if (func_001294B0(sp + 0x100, sp, 4, 1) == 0) {
        return;
    }

    s0 = D_00387AD8;
    D_00387AD8 = s0 + 0x90;
    if (s0 == 0) {
        return;
    }
    FLD(s0, 0x20) = 0x5C;
    FLD64(s0, 0x00) = ((s64)0xA000 << 16) | 8;
    FLD64(s0, 0x10) = ((s64)0xE4000000 << 32) | 0x8001;
    FLD64(s0, 0x18) = ((((s64)0x421421 << 16) | 0x4214) << 16) | 0x2160;

    /* four vectors: sp+0x40 + 16k (value), sp+0x44 (y), sp+0x48 (1.0), sp+0x4C (0) */
    for (s1 = 0; s1 < 4; s1++) {
        k16 = s1 * 16;
        a1 = (s1 + ((u32)s1 >> 31)) >> 1;
        f0 = FLDF(T, 0x4C);
        f3 = FLDF(T, 0x90);
        v1 = s1 - a1 * 2;
        f1 = (f32)v1 * f0;
        f1 = f1 + f3;
        FLDF(sp + 0x40 + k16, 0) = f1;
        f2 = (f32)a1;
        f12 = (f32)FLD(sp + 0x10C + k16, 0);
        f12 = 1.0f / f12;
        f0 = FLDF(T, 0x50);
        f1 = FLDF(T, 0x98);
        f2 = f2 * f0;
        f2 = f2 + f1;
        FLDF(sp + 0x44 + k16, 0) = f2;
        FLDF(sp + 0x48 + k16, 0) = 1.0f;
        FLD(sp + 0x4C + k16, 0) = 0;
        func_00129BD0(sp + 0x80 + k16, sp + 0x40 + k16, f12);
    }

    if (FLD(T, 0x40) & 0x10) {
        for (s1 = 3; s1 >= 0; s1--) {
            FLD(sp + 0x138 - 0x10 * (3 - s1), 0) = 0xFFFFFF;
        }
    }

    total = FLD(sp, 0x108) + FLD(sp, 0x138) + (FLD(sp, 0x128) + FLD(sp, 0x118));
    s1 = total >> 10;
    func_00129D40(sp + 0x140, T + 0x80, FLD(sp, 0x118), FLD(sp, 0x138));

    s0[0x30] = sp[0x140];
    s0[0x31] = sp[0x144];
    s0[0x32] = sp[0x148];
    s0[0x33] = sp[0x14C];
    FLDF(s0, 0x34) = FLDF(sp, 0x88);
    s0[0x48] = sp[0x140];
    s0[0x49] = sp[0x144];
    s0[0x4A] = sp[0x148];
    s0[0x4B] = sp[0x14C];
    FLDF(s0, 0x4C) = FLDF(sp, 0x98);
    s0[0x60] = sp[0x140];
    s0[0x61] = sp[0x144];
    s0[0x62] = sp[0x148];
    s0[0x63] = sp[0x14C];
    FLDF(s0, 0x64) = FLDF(sp, 0xA8);
    s0[0x78] = sp[0x140];
    s0[0x79] = sp[0x144];
    s0[0x7A] = sp[0x148];
    s0[0x7B] = sp[0x14C];
    FLDF(s0, 0x7C) = FLDF(sp, 0xB8);
    FLDF(s0, 0x38) = FLDF(sp, 0x80);
    FLDF(s0, 0x3C) = FLDF(sp, 0x84);
    FLDF(s0, 0x50) = FLDF(sp, 0x90);
    FLDF(s0, 0x54) = FLDF(sp, 0x94);
    FLDF(s0, 0x68) = FLDF(sp, 0xA0);
    FLDF(s0, 0x6C) = FLDF(sp, 0xA4);
    FLDF(s0, 0x80) = FLDF(sp, 0xB0);
    FLDF(s0, 0x84) = FLDF(sp, 0xB4);

    FLDU16(s0, 0x40) = FLDU16(sp, 0x100);
    FLDU16(s0, 0x42) = FLDU16(sp, 0x104);
    PACK_COL(s0, 0x40, FLD(sp, 0x108));
    FLDU16(s0, 0x58) = FLDU16(sp, 0x110);
    FLDU16(s0, 0x5A) = FLDU16(sp, 0x114);
    PACK_COL(s0, 0x58, FLD(sp, 0x118));
    FLDU16(s0, 0x70) = FLDU16(sp, 0x120);
    FLDU16(s0, 0x72) = FLDU16(sp, 0x124);
    PACK_COL(s0, 0x70, FLD(sp, 0x128));
    FLDU16(s0, 0x88) = FLDU16(sp, 0x130);
    FLDU16(s0, 0x8A) = FLDU16(sp, 0x134);
    PACK_COL(s0, 0x88, FLD(sp, 0x138));
    FLD64(s0, 0x28) = FLD64(T, 0xC0);

    if (s1 >= 0) {
        if (s1 < 0x1000) {
            e1 = D_00387AE0 + (2 * s1 + sp150[0]) * 8;
        } else {
            e1 = D_00387AE0 + sp150[0] * 8 + 0xFFF0;
        }
    } else {
        e1 = D_00387AE0 + sp150[0] * 8;
    }
    X = FLD(e1, 4);
    FLD(X, 4) = (s32)s0;
    FLD(e1, 4) = (s32)s0;
    return;
}
