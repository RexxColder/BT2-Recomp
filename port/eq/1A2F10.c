#include "common.h"

extern f32 D_00384E6C;

extern u8 *func_001A2208(u8 *owner);
extern s32 rand(void);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Mtx_RotateX(u8 *dst, u8 *src, f32 ang);
extern void Mtx_RotateZ(u8 *dst, u8 *src, f32 ang);
extern void func_00129C50(u8 *dst, u8 *mtx, u8 *vec);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void func_00129BB8(u8 *dst, u8 *src, f32 s);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);

#define RANDF() ((f32)rand() / D_00384E6C)

/* Spawns one particle `f` from the pool of `owner` (matrices at owner+0x80/+0xC0): position/velocity are a
   random spread rotated by a random X angle plus the given Z angle, then through the owner matrices; size and
   colour ramps (cfg P) are randomised and scaled by gScale[1]. Returns 0 when the pool is full, else 1. */
s32 func_001A2F10(u8 *P, u8 *Q, u8 *owner, u8 *gScale, u32 kind, f32 zAng) {
    u8 *f;
    u8 *mtx;
    u8 *pos;
    u8 *vel;
    u8 *acc;
    u8 up[0x10];
    u8 tmp[0x10];
    f32 life, ang, v, v1, v2, k;

    f = func_001A2208(owner);
    if (f == 0) {
        return 0;
    }
    Vec4_Set(up, 1.0f, 0.0f, 0.0f, 1.0f);
    *(u32 *)f |= 1;
    if ((rand() & 1) == 0) {
        *(u32 *)f |= 0x20;
    }
    pos = f + 0x40;
    *(f32 *)(f + 8) = 0.0f;
    life = (*(f32 *)(P + 0x10) + *(f32 *)(P + 0x14) * RANDF()) * 30.0f;
    *(f32 *)(f + 0xC) = life;
    *(f32 *)(f + 0x10) = life * *(f32 *)(P + 0x18);
    f[6] = 1;
    f[5] = (u8)kind;
    *(f32 *)(f + 0x14) = life - *(f32 *)(P + 0x74);
    mtx = f + 0xE0;
    vel = f + 0x60;
    Vec4_Set(pos, 0.0f, 0.0f, 0.0f, 1.0f);
    ang = (*(f32 *)(P + 0x78) - *(f32 *)(P + 0x7C)) * 0.5f * RANDF() + *(f32 *)(P + 0x7C) * 0.5f;
    Vec4_Set(vel, 0.0f, 0.0f, 1.0f, 1.0f);
    Mtx_RotateX(mtx, owner + 0x80, ang);
    Mtx_RotateZ(mtx, mtx, zAng);
    func_00129C50(vel, mtx, vel);
    func_00129C50(vel, owner + 0xC0, vel);
    func_00129BD0(pos, vel, *(f32 *)(P + 0x20) + *(f32 *)(P + 0x24) * RANDF());
    *(f32 *)(f + 0x4C) = 1.0f;
    if (0.0f < *(f32 *)(P + 0x1C)) {
        Vec4_Set(tmp, 0.0f, *(f32 *)(P + 0x1C), 0.0f, 1.0f);
        func_00129C50(tmp, mtx, tmp);
        func_00129C50(tmp, owner + 0xC0, tmp);
        Vec3_Add(pos, pos, tmp);
        *(f32 *)(f + 0x4C) = 1.0f;
    }
    acc = f + 0x70;
    vel = f + 0x90;

    v = *(f32 *)(P + 0x58) + *(f32 *)(P + 0x5C) * RANDF();
    *(f32 *)(f + 0x18) = *(f32 *)(gScale + 4) * v;
    v = *(f32 *)(P + 0x40) + *(f32 *)(P + 0x44) * RANDF();
    *(f32 *)(f + 0x1C) = *(f32 *)(gScale + 4) * v;
    v = *(f32 *)(P + 0x60) + *(f32 *)(P + 0x64) * RANDF();
    *(f32 *)(f + 0x20) = (v - *(f32 *)(f + 0x18)) / *(f32 *)(f + 0x10);
    v = *(f32 *)(P + 0x48) + *(f32 *)(P + 0x4C) * RANDF();
    *(f32 *)(f + 0x24) = (v - *(f32 *)(f + 0x1C)) / *(f32 *)(f + 0x10);
    func_00129C50(acc, mtx, up);
    func_00129C50(acc, owner + 0xC0, acc);

    *(f32 *)(f + 0x80) = *(f32 *)(Q + 0x10) * RANDF();
    *(f32 *)(f + 0x84) = *(f32 *)(Q + 0x14) * RANDF();
    *(f32 *)(f + 0x88) = *(f32 *)(Q + 0x18) * RANDF();
    Vec3_Add(f + 0x80, f + 0x80, Q);
    *(f32 *)(f + 0x8C) = 0.0f;
    *(f32 *)(f + 0x90) = *(f32 *)(Q + 0x30) * RANDF();
    *(f32 *)(f + 0x94) = *(f32 *)(Q + 0x34) * RANDF();
    *(f32 *)(f + 0x98) = *(f32 *)(Q + 0x38) * RANDF();
    Vec3_Add(vel, vel, Q + 0x20);
    Vec3_Sub(vel, vel, Q);
    func_00129BD0(vel, vel, 1.0f / *(f32 *)(f + 0xC));
    v = *(f32 *)(Q + 0xC) + *(f32 *)(Q + 0x1C) * RANDF();
    *(f32 *)(f + 0x9C) = v / *(f32 *)(P + 0x70);
    *(f32 *)(f + 0x30) = *(f32 *)(P + 0x28) + *(f32 *)(P + 0x2C) * RANDF();
    v = *(f32 *)(P + 0x30) + *(f32 *)(P + 0x34) * RANDF();
    v1 = (v - *(f32 *)(f + 0x30)) / *(f32 *)(f + 0x10);
    *(f32 *)(f + 0x34) = v1;
    k = *(f32 *)(gScale + 4);
    *(f32 *)(f + 0x30) = *(f32 *)(f + 0x30) * k;
    *(f32 *)(f + 0x34) = v1 * k;
    *(f32 *)(f + 0x1C) = *(f32 *)(f + 0x1C) * k;
    *(f32 *)(f + 0x24) = *(f32 *)(f + 0x24) * k;
    *(f32 *)(f + 0x18) = *(f32 *)(f + 0x18) * k;
    *(f32 *)(f + 0x20) = *(f32 *)(f + 0x20) * k;
    func_00129BB8(vel, vel, 1.0f);
    return 1;
}
