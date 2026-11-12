#include "common.h"

#define SPU64(o) (*(u64 *)(sp + (o)))
#define SPS32(o) (*(s32 *)(sp + (o)))
#define SPF32(o) (*(f32 *)(sp + (o)))

extern s32 D_00387850;

s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00129C28(s32 arg0, s32 arg1);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
s32 EftChain2_Create(s32 arg0);
void EftChain2_SetRes(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftChain2_SetType(s32 arg0, s32 arg1);
s32 func_001CC978(s32 arg0);
void func_001CCC68(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001CCD10(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, s32 arg2);

void func_001AD848(s32 arg0, s32 arg1) {
    u8 sp[0x130];
    u8 *s3;
    u8 *T;
    u8 *s1;
    u8 *s4;
    u8 *s6;
    u8 *p2;
    s32 s7;
    s32 off;
    s32 P;
    s32 C;
    s32 R;
    u64 t0;
    u64 t1;
    u64 t2;
    u64 t3;
    u64 v0;
    u64 v1;
    u64 a2;
    u64 a3;
    s32 k;

    T = (u8 *)D_00387850;
    s3 = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    s4 = T + 0x10;
    p2 = (u8 *)arg1;

    memset(s3, 0, 0x70);
    *(u64 *)(s3 + 0x00) = *(u64 *)(p2 + 0x00);
    *(u64 *)(s3 + 0x08) = *(u64 *)(p2 + 0x08);
    *(u64 *)(s3 + 0x10) = *(u64 *)(p2 + 0x10);
    *(u64 *)(s3 + 0x18) = *(u64 *)(p2 + 0x18);
    s1 = s3 + 0x50;
    s6 = s4;
    SPS32(0x120) = (s32)(s3 + 0x40);
    SPS32(0x124) = (s32)(T + 0x0C);
    func_00208DE8(*(s32 *)(p2 + 0x10), (s32)(s3 + 0x30), *(s32 *)(p2 + 0x14));
    func_00129C28((s32)(s3 + 0x40), (s32)s3);
    *(f32 *)(s3 + 0x28) = *(f32 *)(p2 + 0x1C);
    *(s32 *)(s3 + 0x24) = *(s32 *)(s3 + 0x18);
    SPS32(0x50) = 0;

    for (s7 = 0; s7 < 3; s7++) {
        SPS32(0x50) = 0;
        off = s7 * 4;
        SPF32(0x54) = *(f32 *)((u8 *)(*(s32 *)T) + off);
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);
        SPS32(0x80) = 0;
        SPS32(0x84) = (s32)s6;
        SPS32(0x88) = *(s32 *)(T + 0x350 + off);
        SPS32(0x8C) = *(s32 *)(T + 0x35C + off) + 80 * *(s32 *)(s3 + 0x24);
        SPS32(0x90) = *(s32 *)(p2 + 0x10);
        for (k = 0; k < 8; k++) {
            *(u64 *)(sp + 8 * k) = *(u64 *)(sp + 0x50 + 8 * k);
        }
        SPU64(0x40) = SPU64(0x90);
        SPU64(0x48) = SPU64(0x98);
        func_00129C28((s32)(sp + 0x10), (s32)(s3 + 0x30));
        func_00129C28((s32)(sp + 0x20), SPS32(0x120));
        P = EftPtcl3_Create((s32)sp);
        *(s32 *)s1 = P;
        EftPtcl3_SetTexture(P, (s32)s4, 0, *(s32 *)(s3 + 0x24));
        s4 += 0x118;
        EftPtcl3_SetType(*(s32 *)s1, 2);
        s1 += 4;
        s6 += 0x118;
    }

    SPS32(0xA0) = *(s32 *)(s3 + 0x10);
    SPS32(0xA8) = 0;
    SPS32(0xA4) = *(s32 *)(s3 + 0x24);
    SPF32(0xAC) = *(f32 *)((u8 *)(*(s32 *)T) + 0x0C);
    memset(sp + 0xB0, 0, 0x10);
    memset(sp + 0xC0, 0, 0x10);
    SPS32(0xD4) = (s32)(T + 0x370);
    SPS32(0xD0) = 0;
    SPS32(0xD8) = *(s32 *)(T + 0x480);
    SPS32(0xDC) = *(s32 *)(T + 0x484) + (*(s32 *)(s3 + 0x24) << 6);

    t3 = SPU64(0xA0);
    t2 = SPU64(0xA8);
    t1 = SPU64(0xB0);
    t0 = SPU64(0xB8);
    v0 = SPU64(0xC8);
    a3 = SPU64(0xC0);
    v1 = SPU64(0xD0);
    a2 = SPU64(0xD8);
    SPU64(0x50) = t3;
    SPU64(0x58) = t2;
    SPU64(0x60) = t1;
    SPU64(0x68) = t0;
    SPU64(0x70) = a3;
    SPU64(0x80) = v1;
    SPU64(0x88) = a2;
    SPU64(0x78) = v0;

    func_00129C28((s32)(sp + 0x70), (s32)(s3 + 0x30));
    func_00129C28((s32)(sp + 0x60), SPS32(0x120));
    C = EftChain2_Create((s32)(sp + 0x50));
    *(s32 *)(s3 + 0x60) = C;
    EftChain2_SetRes(C, (s32)(T + 0x370), 0, *(s32 *)(s3 + 0x24));
    EftChain2_SetType(*(s32 *)(s3 + 0x60), 2);

    /* the asm reuses s1 here (addiu s1,s5,0x490): the texture table T+0x490, not the handle array of the loop */
    s1 = T + 0x490;
    SPS32(0xE0) = *(s32 *)(s3 + 0x10);
    SPS32(0xE4) = 0;
    SPS32(0xE8) = 0;
    SPF32(0xEC) = *(f32 *)((u8 *)(*(s32 *)T) + 0x10);
    memset(sp + 0xF0, 0, 0x10);
    memset(sp + 0x100, 0, 0x10);
    SPS32(0x110) = (s32)s1;
    SPS32(0x114) = *(s32 *)(T + 0x5A0);
    SPS32(0x118) = *(s32 *)(T + 0x5A4) + (*(s32 *)(s3 + 0x24) << 4);

    t0 = SPU64(0xF8);
    a3 = SPU64(0x100);
    t3 = SPU64(0xE0);
    t2 = SPU64(0xE8);
    v0 = SPU64(0x108);
    t1 = SPU64(0xF0);
    a2 = SPU64(0x118);
    v1 = SPU64(0x110);
    SPU64(0xA8) = t0;
    SPU64(0xB0) = a3;
    SPU64(0xC8) = a2;
    SPU64(0x90) = t3;
    SPU64(0x98) = t2;
    SPU64(0xA0) = t1;
    SPU64(0xB8) = v0;
    SPU64(0xC0) = v1;

    func_00129C28((s32)(sp + 0xA0), (s32)(s3 + 0x30));
    func_00129C28((s32)(sp + 0xB0), SPS32(0x120));
    R = func_001CC978((s32)(sp + 0x90));
    *(s32 *)(s3 + 0x5C) = R;
    func_001CCC68(R, (s32)s1, 0, *(s32 *)(s3 + 0x24));
    func_001CCD10(*(s32 *)(s3 + 0x5C), 2);
}
