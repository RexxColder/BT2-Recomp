#include "common.h"

extern s32 rand();
extern u8 *EftGlow_AllocPart(void);
s32 func_001977A0(u8 *e, s32 a1, s32 a2);
void Vec4_Set(u8 *out, f32 x, f32 y, f32 z, f32 w);
f32 EftGlow_CalcWidth(u8 *p, s32 which);
f32 EftGlow_CalcLength(u8 *p, s32 which);
f32 EftGlow_GetAlpha(u8 *e, s32 flags, s32 idx);
void EftGlow_GetShapeDir(u8 *out, s32 objId, s32 shape, f32 dirY);
void func_00129BD0(u8 *out, u8 *in, f32 scale);
void func_00129C28(u8 *out, u8 *in);
void func_00129B58(u8 *out, u8 *a, u8 *b);
void Vec3_Sub(u8 *out, u8 *a, u8 *b);
extern u8 *gEftGlowCfg;
extern u8 *gEftGlowCfg2;
extern f32 D_00384CD4, D_00384CD8, D_00384CDC, D_00384CE0, D_00384CE4, D_00384CE8, D_00384CEC;
extern f32 D_00384CF0, D_00384CF4, D_00384CF8, D_00384CFC, D_00384D00, D_00384D04, D_00384D08;
extern f32 D_00384D0C, D_00384D10;

#define F(off) (*(f32 *)(p + (off)))

u8 *EftGlow_SpawnPart(u8 *e, s32 objId, u8 *scale, s32 odd, s32 pair, f32 angle) {
    u8 d[16];
    u8 *p;
    s32 shape;
    s32 idx;
    f32 alpha;
    f32 inv;
    f32 one;
    u8 *k;
    u32 flags;
    s32 node;

    p = EftGlow_AllocPart();
    shape = *(s32 *)(gEftGlowCfg + *(s32 *)(e + 0x14) * 24 + 0x494);
    idx = rand() % *(s32 *)(e + 0x24);
    if (p == 0) {
        return 0;
    }
    *(u32 *)p = func_001977A0(e, pair & 0xFF, odd & 0xFF);
    if ((pair & 0xFF) != 0) {
        p[4] = 1;
    } else {
        p[4] = 0;
    }
    flags = *(u32 *)p;
    if (flags & 2) {
        p[5] = 3;
    } else if (flags & 0x20) {
        p[5] = 2;
    } else if (flags & 0x40) {
        p[5] = 0;
    } else {
        p[5] = 1;
    }
    F(0x10) = *(f32 *)(gEftGlowCfg2 + 0x1C) + *(f32 *)(gEftGlowCfg2 + 0x20) * ((f32)rand() / D_00384CD4);
    if (*(u32 *)p & 8) {
        F(0x10) = F(0x10) * D_00384CD8;
    }
    p[7] = objId;
    F(0x14) = F(0x10);
    F(0x38) = angle;
    p[0xD] = e[0x14];
    Vec4_Set(p + 0x80, 0.0f, 0.0f, 0.0f, 0.0f);
    F(0x1C) = EftGlow_CalcWidth(p, 0);
    F(0x20) = EftGlow_CalcLength(p, 0);
    F(0x2C) = EftGlow_CalcWidth(p, 1) - F(0x1C);
    F(0x2C) = F(0x2C) / (F(0x10) * *(f32 *)gEftGlowCfg2);
    F(0x30) = EftGlow_CalcLength(p, 1) - F(0x20);
    F(0x30) = F(0x30) / (F(0x10) * *(f32 *)gEftGlowCfg2);
    if (*(u32 *)p & 0x10) {
        p[6] = rand() % *(s32 *)(e + 0x2C);
    }
    alpha = EftGlow_GetAlpha(e, *(s32 *)p, idx);
    k = gEftGlowCfg2 + p[5] * 60 + 0xB4;
    F(0x3C) = *(f32 *)(k + 0) + *(f32 *)(k + 4) * ((f32)rand() / D_00384CD4);
    F(0x34) = *(f32 *)(k + 8) + *(f32 *)(k + 12) * ((f32)rand() / D_00384CD4);
    F(0x18) = (*(f32 *)(k + 16) + *(f32 *)(k + 20) * ((f32)rand() / D_00384CD4)) * *(f32 *)(e + 0x48);
    F(0x24) = *(f32 *)(k + 24) + *(f32 *)(k + 28) * ((f32)rand() / D_00384CD4);
    F(0x28) = *(f32 *)(k + 32) + *(f32 *)(k + 36) * ((f32)rand() / D_00384CD4);
    F(0x7C) = *(f32 *)(k + 40) + *(f32 *)(k + 44) * ((f32)rand() / D_00384CD4);
    F(0x70) = *(f32 *)(scale + 0) * *(f32 *)(k + 48);
    F(0x74) = *(f32 *)(scale + 4) * *(f32 *)(k + 52);
    F(0x78) = *(f32 *)(scale + 8) * *(f32 *)(k + 56);
    flags = *(u32 *)p;
    inv = 0.0f;
    if (flags & 2) {
        if (flags & 0x20) {
            u8 *src = e + idx * 16 + 0x260;
            one = 1.0f;
            p[0xC] = 1;
            func_00129BD0(p + 0x50, src, one);
            F(0x5C) = inv;
            func_00129B58(d, src, p + 0x50);
        } else {
            p[0xC] = 0;
            func_00129C28(p + 0x50, e + 0x190);
            F(0x5C) = inv;
            func_00129B58(d, e + 0x1A0, p + 0x50);
            one = 1.0f;
        }
        func_00129BD0(p + 0x60, d, one / F(0x14));
        F(0x6C) = alpha * (one / *(f32 *)(gEftGlowCfg + 0x1A8));
        F(0x78) = F(0x78) * (((f32)rand() / D_00384CDC) * 1.5f + 1.0f);
        p[0xE] = shape / 2 + rand() % 2;
    } else if (flags & 0x20) {
        p[0xC] = 1;
        func_00129C28(p + 0x50, e + idx * 16 + 0x260);
        F(0x5C) = inv;
        Vec4_Set(p + 0x60, inv, inv, inv, alpha * (1.0f / *(f32 *)(gEftGlowCfg + 0x1A8)));
        if ((u32)(*(s32 *)(e + 0xC) - 3) < 2) {
            F(0x34) = F(0x34) * D_00384CE0;
            node = p[0xD];
            if (node == 0) {
                F(0x34) = F(0x34) * 0.5f;
            } else if (node == 1) {
                F(0x34) = F(0x34) * D_00384CE4;
            } else if ((u8)(node - 3) < 2) {
                F(0x78) = F(0x78) * D_00384CE8;
                F(0x34) = F(0x34) * 0.5f;
            }
        }
        F(0x34) = F(0x34) + D_00384CEC;
        F(0x18) = F(0x18) * D_00384CF0;
        p[0xE] = shape + rand() % 3;
    } else {
        one = 1.0f;
        p[0xC] = 0;
        func_00129BD0(p + 0x50, e + 0x190, ((f32)rand() / D_00384CD4) * D_00384CF4 + one);
        F(0x5C) = inv;
        Vec3_Sub(p + 0x60, e + 0x1A0, p + 0x50);
        func_00129BD0(p + 0x60, p + 0x60, one / F(0x14));
        F(0x6C) = alpha * (one / *(f32 *)(gEftGlowCfg + 0x1A8));
        if ((u32)(*(s32 *)(e + 0xC) - 3) < 2) {
            F(0x3C) = F(0x3C) * D_00384CF8;
            F(0x34) = F(0x34) * D_00384CFC;
            node = p[0xD];
            if (node == 0) {
                F(0x34) = F(0x34) * 0.5f;
            } else if (node == 1) {
                F(0x34) = F(0x34) * D_00384D00;
            } else if ((u8)(node - 3) < 2) {
                F(0x78) = F(0x78) * D_00384D04;
                F(0x34) = F(0x34) * 0.5f;
            }
        } else if ((u8)(p[0xD] - 3) < 2) {
            F(0x34) = F(0x34) * D_00384D08;
        }
        F(0x34) = F(0x34) * D_00384D0C;
        F(0x18) = F(0x18) * D_00384D10;
        p[0xE] = shape + rand() % 4;
    }
    if (p[0xE] >= 0x14) {
        p[0xE] = 0x13;
    }
    EftGlow_GetShapeDir(p + 0x90, objId, p[0xE], F(0x3C));
    p[8] = 0;
    p[9] = rand() % 2;
    p[0xA] = rand() % 2;
    p[0xB] = rand() % (s32)*(f32 *)(gEftGlowCfg2 + 4);
    return p;
}
