#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLD16(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define FLDU16(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define FLD8(p, off) (*(s8 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define CVT_W_S(x) ((s32)(x)) /* cvt.w.s del R5900 trunca hacia cero */

extern u8 *D_003876FC;

void func_003126C8();
f32 func_00123140();
s32 func_002745F8();
f32 func_00273000(void);
f32 func_00273048(void);

f32 func_00123530(void *arg0, s32 arg1) {
    u8 *b = (u8 *)arg0;
    u8 *S = b + 0xBE0;
    u8 *tab;
    u8 *p0;
    u8 *p4;
    u8 *p8;
    u8 *ent;
    u8 *s1p;
    u8 *s4p;
    u8 *P;
    u8 *Q;
    s32 s0;
    s32 s0v;
    s32 s2v;
    s32 s3;
    s32 s6;
    s32 s7;
    s32 t;
    s32 v;
    s32 idx;
    s32 sum;
    f32 f;
    f32 fr;

    tab = (u8 *)FLD(D_003876FC, 0x10);
    func_003126C8(b + 0xC00, b + 0x170);
    t = CVT_W_S(*(f32 *)(b + 0xC04));
    FLD16(b, 0xE00) = (s16)t;
    FLD8(b, 0xEA0) = -1;
    FLD8(b, 0xE80) = -1;
    FLD(b, 0xEC0) = 0;
    FLD16(b, 0xF40) = 0;
    FLD8(b, 0xF80) = -1;
    FLD16(b, 0xE40) = (s16)t;
    FLD8(b, 0xFA0) = 0;
    FLD8(b, 0xFC0) = 0;
    func_003126C8(b + 0xC10, FLD(tab, 0x48) + arg1 * 16, arg1 * 16);

    s0 = *(s8 *)(FLD(tab, 0x64) + arg1);
    if (s0 < 0) {
        FLDU16(b, 0xE02) = *(u16 *)(FLD(tab, 0x5C) + 2 * arg1);
        v = FLD(tab, 0x54);
        FLDU16(b, 0xE42) = *(u16 *)(v + 2 * arg1);
        FLD8(b, 0xE81) = -1;
        FLD8(b, 0xEA1) = -1;
    } else if (func_002745F8(s0) != 0) {
        FLDU16(b, 0xE02) = *(u16 *)(FLD(tab, 0x60) + 2 * arg1);
        v = FLD(tab, 0x58);
        FLDU16(b, 0xE42) = *(u16 *)(v + 2 * arg1);
        FLD8(b, 0xE81) = -1;
        FLD8(b, 0xEA1) = -1;
    } else {
        FLDU16(b, 0xE02) = *(u16 *)(FLD(tab, 0x5C) + 2 * arg1);
        FLDU16(b, 0xE42) = *(u16 *)(FLD(tab, 0x54) + 2 * arg1);
        FLD8(b, 0xE81) = s0;
        FLD8(b, 0xEA1) = s0;
    }

    f = func_00123140(S + 0x20, S + 0x30);
    FLDF(S, 0x2E4) = f;
    FLD8(S, 0x3A1) = -1;
    FLD8(S, 0x3C1) = 4;
    FLD8(S, 0x3E1) = 1;
    sum = FLD16(S, 0x220) + FLD16(S, 0x222);
    f = (f32)sum * 0.5f;
    FLD16(S, 0x362) = (s16)CVT_W_S(f);

    p0 = b + 0x160;
    ent = p0 + arg1 * 8 + 0x30;
    s3 = ent[0xC];
    s6 = (s8)ent[0xD];
    s7 = 2;
    if (s3 != 0xFF) {
        p4 = S + 0x2E8;
        p8 = S + 0x40;
        s1p = S + 0x3E2;
        s4p = S + 0x364;
        do {
            func_003126C8(p8, FLD(tab, 0x48) + s3 * 16);
            s0 = *(s8 *)(FLD(tab, 0x64) + s3);
            if (s0 < 0) {
                FLDU16(s4p, -0x140) = *(u16 *)(FLD(tab, 0x5C) + 2 * s3);
                v = FLD(tab, 0x54);
                FLDU16(s4p, -0x100) = *(u16 *)(v + 2 * s3);
                FLD8(s1p, -0x120) = -1;
                FLD8(s1p, -0x140) = -1;
            } else if (func_002745F8(s0) != 0) {
                FLDU16(s4p, -0x140) = *(u16 *)(FLD(tab, 0x60) + 2 * s3);
                v = FLD(tab, 0x58);
                FLDU16(s4p, -0x100) = *(u16 *)(v + 2 * s3);
                FLD8(s1p, -0x120) = -1;
                FLD8(s1p, -0x140) = -1;
            } else {
                FLDU16(s4p, -0x140) = *(u16 *)(FLD(tab, 0x5C) + 2 * s3);
                FLDU16(s4p, -0x100) = *(u16 *)(FLD(tab, 0x54) + 2 * s3);
                FLD8(s1p, -0x140) = s0;
                FLD8(s1p, -0x120) = s0;
            }

            idx = s3 * FLD(tab, 0xC) + s6;
            *(f32 *)p4 = *(f32 *)(FLD(tab, 0x68) + 4 * idx);
            s0 = *(s8 *)(FLD(tab, 0x7C) + idx);
            if (s0 < 0) {
                FLDU16(s4p, 0) = *(u16 *)(FLD(tab, 0x74) + 2 * idx);
                FLD8(s1p, -0x40) = -1;
            } else if (func_002745F8(s0, p4) != 0) {
                FLDU16(s4p, 0) = *(u16 *)(FLD(tab, 0x78) + 2 * idx);
                FLD8(s1p, -0x40) = -1;
            } else {
                FLDU16(s4p, 0) = *(u16 *)(FLD(tab, 0x74) + 2 * idx);
                FLD8(s1p, -0x40) = s0;
            }

            FLD8(s1p, -0x20) = 0;
            FLD8(s1p, 0) = 1;
            s1p += 1;
            s4p += 2;
            s7 += 1;
            ent = p0 + s3 * 8 + 0x30;
            p4 += 4;
            p8 += 0x10;
            s3 = ent[0xC];
            s6 = (s8)ent[0xD];
        } while (s3 != 0xFF && s7 < 0x20);
    }

    s0v = (s32)S + (s7 << 4);
    s2v = s7 << 1;
    s4p = (u8 *)(s0v + 0x20);
    s1p = S + s2v + 0x220;
    func_003126C8(s4p, p0);
    s3 = -1;
    f = func_00273048();
    FLD16(s1p, 0) = (s16)CVT_W_S(f);
    f = func_00273000();
    P = S + s2v;
    Q = S + s7;
    FLD16(P, 0x260) = (s16)CVT_W_S(f);
    FLD8(Q, 0x2C0) = -1;
    FLD8(Q, 0x2A0) = -1;
    f = func_00123140(s0v + 0x10, s0v + 0x20);
    FLDF(S, (s7 << 2) + 0x2E0) = f;

    v = FLD16(P, 0x21E) + FLD16(s1p, 0);
    s7 += 1;
    fr = (f32)v * 0.5f;
    FLD16(P, 0x360) = (s16)CVT_W_S(fr);
    FLD8(Q, 0x3A0) = -1;
    FLD8(Q, 0x3C0) = 7;
    FLD8(Q, 0x3E0) = 1;
    FLD(S, 0) = (FLD(S, 0) + 1) & 0xFFFF;
    FLD(S, 4) = s7;
    FLD(S, 0x10) = s7 - 1;
    FLD(S, 0xC) = 0;
    FLD(S, 0x14) = 0;
    FLD(S, 8) = 0;
    return fr;
}
