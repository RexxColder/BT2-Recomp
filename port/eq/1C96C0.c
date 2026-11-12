#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern f32 D_003851A8;
extern f32 D_003851AC;

extern u8 *func_001C95C8(u8 *ctx);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern s32 rand(void);
extern void Mtx_RotateX(f32 ang, u8 *dst, u8 *src);
extern void Mtx_RotateZ(f32 ang, u8 *dst, u8 *src);
extern void Mtx_MulVec4(u8 *dst, u8 *mtx, u8 *vec);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec4_Scale(u8 *dst, u8 *src, f32 s);

/* Spawns one particle from emitter cfg (arg0) with ranges in p (arg1) inside ctx (arg2): sets random position,
   velocity, sizes and colour ramps scaled by scale[3] (arg3). t0 is stored at particle[4]. Returns 1 if a
   particle slot was available. */
s32 func_001C96C0(u8 *cfg, u8 *p, u8 *ctx, u8 *scale, s32 t0, f32 ang) {
    u8 sp[0x20];
    u8 *P;
    u8 *rotm;
    u8 *camm;
    u8 *pos;
    u8 *dir;
    u8 *vel;
    u8 *acc;
    f32 x;
    f32 v;
    f32 r;

    P = func_001C95C8(ctx);
    if (P == NULL) {
        return 0;
    }
    Vec4_Set(sp, 1.0f, 0.0f, 0.0f, 1.0f);
    W(P, 0) |= 1;
    if (!(rand() & 1)) {
        W(P, 0) |= 8;
    }
    pos = P + 0x40;
    dir = P + 0x60;
    rotm = P + 0xF0;
    camm = ctx + 0xC0;
    r = (f32)rand();
    F(P, 0x0C) = 0.0f;
    x = (F(cfg, 0x14) + F(cfg, 0x18) * (r / D_003851A8)) * 30.0f;
    F(P, 0x10) = x;
    F(P, 0x14) = x * F(cfg, 0x1C);
    W(P, 0x08) = 1;
    W(P, 0x04) = t0;
    F(P, 0x18) = x - F(cfg, 0x78);
    Vec4_Set(pos, 0.0f, 0.0f, 0.0f, 1.0f);

    r = (f32)rand();
    v = (F(cfg, 0x7C) - F(cfg, 0x80)) * 0.5f * (r / D_003851A8) + F(cfg, 0x80) * 0.5f;
    Vec4_Set(dir, 0.0f, 0.0f, 1.0f, 1.0f);
    Mtx_RotateX(v, rotm, ctx + 0x80);
    Mtx_RotateZ(ang, rotm, rotm);
    Mtx_MulVec4(dir, rotm, dir);
    Mtx_MulVec4(dir, camm, dir);

    r = (f32)rand();
    v = F(cfg, 0x24) + F(cfg, 0x28) * (r / D_003851A8);
    Vec3_Scale(pos, dir, v * F(scale, 0xC));
    F(P, 0x4C) = 1.0f;

    if (F(cfg, 0x20) > 0.0f) {
        Vec4_Set(sp + 0x10, 0.0f, F(cfg, 0x20), 0.0f, 1.0f);
        F(cfg, 0x20) = F(cfg, 0x20) * F(scale, 0xC);
        Mtx_MulVec4(sp + 0x10, rotm, sp + 0x10);
        Mtx_MulVec4(sp + 0x10, camm, sp + 0x10);
        Vec3_Add(pos, pos, sp + 0x10);
        F(P, 0x4C) = 1.0f;
    }

    acc = P + 0xA0;
    vel = P + 0x70;
    Vec3_Sub(acc, scale + 0x20, dir);
    F(P, 0xAC) = 1.0f;
    Vec3_Normalize(acc, acc);
    Vec3_Scale(acc, acc, F(cfg, 0x84));
    Mtx_MulVec4(vel, rotm, sp);
    Mtx_MulVec4(vel, camm, vel);

    F(P, 0x80) = F(p, 0x10) * ((f32)rand() / D_003851A8);
    F(P, 0x84) = F(p, 0x14) * ((f32)rand() / D_003851A8);
    F(P, 0x88) = F(p, 0x18) * ((f32)rand() / D_003851A8);
    Vec3_Add(P + 0x80, P + 0x80, p);
    F(P, 0x8C) = 0.0f;
    F(P, 0x98) = 0.0f;
    F(P, 0x90) = 0.0f;
    F(P, 0x94) = 0.0f;
    r = (f32)rand();
    F(P, 0x9C) = (F(p, 0x0C) + F(p, 0x1C) * (r / D_003851A8)) / F(cfg, 0x74);

    {
        u8 mode = cfg[0];
        s32 doBlock = 0;

        if (mode == 0) {
            doBlock = 1;
        } else if (mode == 1) {
            doBlock = !(rand() & 1);
        }
        if (doBlock) {
            F(P, 0x90) = F(p, 0x30) * ((f32)rand() / D_003851A8);
            F(P, 0x94) = F(p, 0x34) * ((f32)rand() / D_003851A8);
            F(P, 0x98) = F(p, 0x38) * ((f32)rand() / D_003851A8);
            Vec3_Add(P + 0x90, P + 0x90, p + 0x20);
            Vec3_Sub(P + 0x90, P + 0x90, p);
            Vec3_Scale(P + 0x90, P + 0x90, 1.0f / F(P, 0x10));
        }
    }

    r = (f32)rand();
    F(P, 0x34) = F(cfg, 0x2C) + F(cfg, 0x30) * (r / D_003851AC);
    r = (f32)rand();
    F(P, 0x1C) = F(scale, 0xC) * (F(cfg, 0x5C) + F(cfg, 0x60) * (r / D_003851AC));
    r = (f32)rand();
    {
        f32 old34 = F(P, 0x34);
        f32 old1C = F(P, 0x1C);

        F(P, 0x20) = F(scale, 0xC) * (F(cfg, 0x44) + F(cfg, 0x48) * (r / D_003851AC));
        F(P, 0x34) = old34 * F(scale, 0xC);
        F(P, 0x20) = F(P, 0x20) * F(scale, 0xC);
        F(P, 0x1C) = old1C * F(scale, 0xC);
    }
    r = (f32)rand();
    F(P, 0x38) = ((F(cfg, 0x34) + F(cfg, 0x38) * (r / D_003851AC)) * F(scale, 0xC) - F(P, 0x34)) / F(P, 0x14);
    r = (f32)rand();
    F(P, 0x24) = ((F(cfg, 0x64) + F(cfg, 0x68) * (r / D_003851AC)) * F(scale, 0xC) - F(P, 0x1C)) / F(P, 0x14);
    r = (f32)rand();
    F(P, 0x28) = ((F(cfg, 0x4C) + F(cfg, 0x50) * (r / D_003851AC)) * F(scale, 0xC) - F(P, 0x20)) / F(P, 0x14);
    Vec4_Scale(P + 0x90, P + 0x90, 1.0f);
    return 1;
}
