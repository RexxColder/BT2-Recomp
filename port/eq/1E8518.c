#include "common.h"

extern u8 *D_003878F4;
extern f32 D_003856C0;

f32 BtlCharApi_GetHeight(s32 objId);
s32 BtlScene_IsCharStopped(s32 objId);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00129C28(void *arg0, void *arg1);
void func_0018E1A8(s32 arg0, void *arg1);
void EftPtcl3_SetPos(s32 arg0, void *arg1);
void EftChain2_SetPos(s32 arg0, void *arg1);
s32 EftPtcl3_Create(void *arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
s32 EftQuad_Create(void *arg0);
void func_0018E5E0(s32 arg0, s32 arg1);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_001E70B0(f32 farg0, void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5, void *arg6, s32 arg7);
void func_001E7178(void *arg0);
void func_001E7208(void *arg0, s32 arg1);
void func_001E7238(void *arg0, void *arg1);
void func_001E8450(void *arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

#define SP_F32(o) (*(f32 *)(sp + (o)))
#define SP_S32(o) (*(s32 *)(sp + (o)))
#define SP_PTR(o) (*(u8 **)(sp + (o)))
#define SP_S64(o) (*(s64 *)(sp + (o)))
#define F32_AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

void func_001E8518(u8 *arg0) {
    s64 spbuf[0x1F0 / 8];
    u8 *sp = (u8 *)spbuf;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    u8 *fp;
    s32 cnt;
    s32 i;

    SP_PTR(0x180) = arg0;
    s2 = PTR_AT(arg0, 0x38);
    s3 = D_003878F4 + 0x210;
    s5 = PTR_AT(s3, 0);
    fp = s2 + 0x68;
    if (BtlScene_IsCharStopped(S32_AT(fp, 0)) != 0) {
        return;
    }

    s6 = s2 + 0x40;
    s4 = s2 + 0x50;
    s1 = s2 + 0x6C;
    SP_PTR(0x188) = s5 + 4;
    s7 = s3 + (S32_AT(s2, 0x64) * 0x840) + 8;
    cnt = 1;
    F32_AT(s2, 0x60) = BtlCharApi_GetHeight(S32_AT(fp, 0)) / D_003856C0;
    func_00208DE8(S32_AT(fp, 0), s6, 3);
    func_00208DE8(S32_AT(fp, 0), s4, 0);

    s0 = s5 + 0x34;
    do {
        func_00129C28(sp, s6);
        {
            f32 f0 = F32_AT(s0, 0);
            f32 f2 = F32_AT(s2, 0x60);
            f32 f1;
            s32 a0;
            cnt -= 1;
            f1 = SP_F32(0x4);
            a0 = S32_AT(s1, 0);
            f0 = f0 * f2;
            s0 += 4;
            f1 = f1 + f0;
            SP_F32(0x4) = f1;
            s1 += 4;
            func_0018E1A8(a0, sp);
        }
    } while (cnt >= 0);

    SP_PTR(0x184) = s2 + 4;
    s0 = s2 + 0x74;
    s1 = SP_PTR(0x188) + 0x20;
    cnt = 2;
    do {
        func_00129C28(sp, s4);
        {
            f32 f0 = F32_AT(s1, 0);
            f32 f2 = F32_AT(s2, 0x60);
            f32 f1;
            s32 a0;
            cnt -= 1;
            f1 = SP_F32(0x4);
            f0 = f0 * f2;
            s1 += 4;
            f1 = f1 + f0;
            SP_F32(0x4) = f1;
            a0 = S32_AT(s0, 0);
            s0 += 4;
            EftPtcl3_SetPos(a0, sp);
        }
    } while (cnt >= 0);

    func_00129C28(sp, s6);
    {
        f32 f1 = F32_AT(s5, 0x3C) * F32_AT(s2, 0x60);
        f32 f0 = SP_F32(0x4) + f1;
        SP_F32(0x4) = f0;
    }
    func_001E7238(s2 + 0x88, sp);
    cnt = 3;
    func_00129C28(sp, s6);
    {
        f32 f1 = F32_AT(s5, 0x48) * F32_AT(s2, 0x60);
        f32 f0 = SP_F32(0x4) + f1;
        SP_F32(0x4) = f0;
    }
    EftChain2_SetPos(S32_AT(s2, 0x90), sp);

    if ((S32_AT(s2, 0x38) & 4) != 0) {
        func_00208DE8(S32_AT(s2, 0x68), s6, 3);

        if ((S32_AT(s2, 0x38) & 8) == 0) {
            /* frame: sp+0x50 / 0x54 / 0x58 hold the ints and pointer for the Vec4 copies */
            SP_S32(0x50) = S32_AT(s7, 0x98) + 0xB4;
            s4 = s7 + 0x1C8;
            SP_PTR(0x58) = s7 + 8;
            SP_S32(0x54) = S32_AT(s7, 0x9C) + 0x40;
            memset(sp + 0x60, 0, 0x10);
            memset(sp + 0x70, 0, 0x10);

            SP_F32(0x80) = F32_AT(s2, 0x60);
            s0 = sp + 0x10;
            SP_F32(0x84) = F32_AT(s5, 0x8);
            {
                s64 t_v1 = SP_S64(0x68);
                s64 t_a1 = SP_S64(0x78);
                s64 t_a2;
                s64 t_a3;
                s64 t_t2;
                s64 t_t1;
                s64 t_t0;
                s64 t_v0;
                SP_S32(0x88) = S32_AT(fp, 0);
                t_a2 = SP_S64(0x80);
                t_a3 = SP_S64(0x88);
                t_t2 = SP_S64(0x50);
                t_t1 = SP_S64(0x58);
                t_t0 = SP_S64(0x60);
                t_v0 = SP_S64(0x70);
                SP_S64(0x28) = t_v1;
                SP_S64(0x38) = t_a1;
                SP_S64(0x40) = t_a2;
                SP_S64(0x48) = t_a3;
                SP_S64(0x10) = t_t2;
                SP_S64(0x18) = t_t1;
                SP_S64(0x20) = t_t0;
                SP_S64(0x30) = t_v0;
            }
            Vec4_Set(sp + 0x30, 0.0f, 1.0f, 0.0f, 1.0f);

            func_00129C28(sp + 0x20, s6);
            {
                f32 f1 = F32_AT(s5, 0x38) * F32_AT(s2, 0x60);
                f32 f0 = SP_F32(0x24) + f1;
                SP_F32(0x24) = f0;
            }
            S32_AT(s2, 0x70) = EftQuad_Create(s0);
            func_0018E5E0(S32_AT(s2, 0x70), 2);

            SP_F32(0xE0) = F32_AT(s5, 0xC);
            SP_F32(0xE4) = F32_AT(s2, 0x60);
            memset(sp + 0xF0, 0, 0x10);
            memset(sp + 0x100, 0, 0x10);

            SP_S32(0x110) = cnt;
            s3 = sp + 0xE0;
            SP_PTR(0x114) = s4;
            s1 = sp + 0x90;
            SP_S32(0x118) = S32_AT(s7, 0x2D8) + 0x42C;
            SP_S32(0x11C) = S32_AT(s7, 0x2DC) + 0xF0;
            SP_S32(0x120) = S32_AT(fp, 0);

            /* struct copy 0xE0..0x11F -> 0x90..0xCF */
            {
                u8 *a2 = s3;
                u8 *a3 = s1;
                do {
                    *(s64 *)(a3 + 0x00) = *(s64 *)(a2 + 0x00);
                    *(s64 *)(a3 + 0x08) = *(s64 *)(a2 + 0x08);
                    *(s64 *)(a3 + 0x10) = *(s64 *)(a2 + 0x10);
                    *(s64 *)(a3 + 0x18) = *(s64 *)(a2 + 0x18);
                    a2 += 0x20;
                    a3 += 0x20;
                } while (a2 != sp + 0x120);
                *(s64 *)(a3 + 0x00) = *(s64 *)(a2 + 0x00);
                *(s64 *)(a3 + 0x08) = *(s64 *)(a2 + 0x08);
            }
            func_00129C28(sp + 0xA0, s6);
            {
                f32 f1 = F32_AT(s5, 0x30) * F32_AT(s2, 0x60);
                f32 f0 = SP_F32(0xA4) + f1;
                SP_F32(0xA4) = f0;
            }
            Vec4_Set(sp + 0xB0, 0.0f, -1.0f, 0.0f, 1.0f);

            {
                s32 h = EftPtcl3_Create(s1);
                S32_AT(s2, 0x80) = h;
                EftPtcl3_SetType(h, 2);
            }

            SP_F32(0x130) = F32_AT(s5, 0x20);
            SP_F32(0x134) = F32_AT(s2, 0x60);
            memset(sp + 0x140, 0, 0x10);
            memset(sp + 0x150, 0, 0x10);

            /* struct copy 0x130..0x16F -> 0xE0..0x11F (2 chunks + tail) */
            SP_S32(0x160) = 4;
            SP_PTR(0x164) = s4;
            SP_S32(0x168) = S32_AT(s7, 0x2D8) + 0x590;
            SP_S32(0x16C) = S32_AT(s7, 0x2DC) + 0x140;
            SP_S32(0x170) = S32_AT(fp, 0);
            {
                u8 *a2 = s3;
                u8 *a3 = sp + 0x130;
                do {
                    *(s64 *)(a2 + 0x00) = *(s64 *)(a3 + 0x00);
                    *(s64 *)(a2 + 0x08) = *(s64 *)(a3 + 0x08);
                    *(s64 *)(a2 + 0x10) = *(s64 *)(a3 + 0x10);
                    *(s64 *)(a2 + 0x18) = *(s64 *)(a3 + 0x18);
                    a3 += 0x20;
                    a2 += 0x20;
                } while (a3 != sp + 0x170);
                *(s64 *)(a2 + 0x00) = *(s64 *)(a3 + 0x00);
                *(s64 *)(a2 + 0x08) = *(s64 *)(a3 + 0x08);
            }
            s1 = s2 + 0x8C;
            func_00129C28(sp + 0xF0, s6);
            {
                f32 f1 = F32_AT(s5, 0x4C) * F32_AT(s2, 0x60);
                f32 f0 = SP_F32(0xF4) + f1;
                SP_F32(0xF4) = f0;
            }
            Vec4_Set(sp + 0x100, 0.0f, -1.0f, 0.0f, 1.0f);

            {
                s32 h = EftPtcl3_Create(s3);
                S32_AT(s2, 0x84) = h;
                EftPtcl3_SetType(h, 2);
            }

            {
                f32 f20 = F32_AT(s5, 0x10) * F32_AT(s2, 0x60);
                s0 = sp + 0x50;
                func_00129C28(s0, s6);
                {
                    f32 f1 = F32_AT(s5, 0x14) * F32_AT(s2, 0x60);
                    f32 f0 = SP_F32(0x54) + f1;
                    SP_F32(0x54) = f0;
                }
                func_001E70B0(f20, s1, S32_AT(s7, 0x714), 0, 0, 0, s0, s7 + 0x500, S32_AT(fp, 0));
            }
            func_001E7208(s1, 2);
            func_001E8450(SP_PTR(0x180));
        }
        S32_AT(s2, 0x38) = S32_AT(s2, 0x38) | 8;
    }

    for (i = 0; i < 2; i++) {
        func_001E7178(s2 + 0x88 + 4 * i);
    }
}
