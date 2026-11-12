#include "common.h"

extern u8 *func_001B8AA0(u8 *sys);
extern s32 rand();
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Add(u8 *dst, u8 *a, u8 *b);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_00129C50(u8 *dst, u8 *mtx, u8 *vec);
extern void func_0012A360(u8 *dst, u8 *dir, u8 *base, f32 len);
extern void Mtx_RotateX(u8 *dst, u8 *src, f32 ang);
extern void Mtx_RotateY(u8 *dst, u8 *src, f32 ang);
extern void Mtx_RotateZ(u8 *dst, u8 *src, f32 ang);

#define F(base, off) (*(f32 *)((base) + (off)))
#define RMAX 2147483520.0f
#define RF() ((f32)rand() / RMAX)
#define PI_ 3.141592503f
#define TWO_PI 6.283185005f

/* Wrap an angle stored at p into (-pi, pi). */
static void wrap_angle(f32 *p)
{
    f32 a = *p;
    if (PI_ <= a) {
        *p = a - TWO_PI;
    } else if (a <= -PI_) {
        *p = a + TWO_PI;
    }
}

/* Spawn `count` particles of an emitter into particle system `sys`. ctx+0x38 = emitter config, ctx+0x3C = range
 * table, ctx+0x20 = origin vector, ctx+4 = scale. Returns 0 when no particle could be allocated. */
s32 func_001B9470(u8 *sys, u8 *ctx, s32 count)
{
    u8 mtx[0x40] __attribute__((aligned(16)));
    u8 tmp40[0x10] __attribute__((aligned(16)));
    u8 tmp50[0x10] __attribute__((aligned(16)));
    u8 tmp60[0x10] __attribute__((aligned(16)));
    u8 *cfg = *(u8 **)(ctx + 0x38);
    u8 *tb = *(u8 **)(ctx + 0x3C);
    u8 *q = cfg + 0xE0;
    u8 *p;
    u8 *dir;
    u8 *mat;
    u8 *pos;
    u8 *vel;
    f32 f;

    if (count <= 0) {
        return 1;
    }
    do {
        p = func_001B8AA0(sys);
        if (p == 0) {
            return 0;
        }
        *(u32 *)p |= 1;
        if (cfg[7] == 1 && (rand() & 1) == 0) {
            *(u32 *)p |= 0x20;
        }
        f = (F(cfg, 0x68) + F(cfg, 0x6C) * RF()) * 30.0f;
        *(u32 *)(p + 8) = 0;
        F(p, 0xC) = f;
        F(p, 0x10) = f * F(cfg, 0x70);
        *(u32 *)(p + 0x18) = 0;
        F(p, 0x14) = f - F(cfg, 0xCC);
        F(p, 0x1C) = F(cfg, 0xC4) * 30.0f;
        if (cfg[0x158] == 1) {
            F(p, 0x18) = F(p, 0x1C) * RF();
        }
        F(p, 0x20) = F(cfg, 0xC0) - F(cfg, 0xBC);
        p[5] = cfg[8];
        dir = p + 0x90;
        if (cfg[2] == 1) {
            Vec4_Set(dir, 0.0f, F(cfg, 0xD4), 0.0f, 1.0f);
            Vec3_Normalize(dir, dir);
        } else {
            f32 ang;
            mat = p + 0xE0;
            ang = ((F(sys, 0x12C) - F(sys, 0x130)) * 0.5f) * RF() + F(sys, 0x130) * 0.5f;
            Vec4_Set(dir, 0.0f, 0.0f, 1.0f, 1.0f);
            Mtx_RotateX(mat, sys + 0x1D0, ang);
            Mtx_RotateZ(mat, mat, F(sys, 0x258));
            func_00129C50(dir, mat, dir);
            F(dir, 0) = F(dir, 0) * (F(cfg, 0x154) + 1.0f);
            Vec3_Normalize(dir, dir);
            func_00129C50(dir, sys + 0x210, dir);
        }
        vel = p + 0x60;
        pos = p + 0x50;
        f = (F(cfg, 0x124) + F(cfg, 0x128) * RF()) * F(ctx, 4);
        Vec3_Scale(pos, dir, f);
        F(p, 0x5C) = 1.0f;
        Vec4_Set(vel, 0.0f, 0.0f, 0.0f, 1.0f);
        {
            f32 r1 = (f32)rand();
            f32 r2 = (f32)rand();
            f = (F(q, 0) + F(q, 4) * (r1 / RMAX)) * (r2 / RMAX);
        }
        {
            f32 r3 = (f32)rand();
            f32 r4 = (f32)rand();
            f += (F(q, 8) + F(q, 0xC) * (r3 / RMAX)) * (r4 / RMAX);
        }
        f *= F(ctx, 4);
        switch (cfg[6]) {
        case 0:
            Vec4_Set(vel, 0.0f, 0.0f, f, 1.0f);
            Mtx_RotateX(mtx, sys + 0x1D0, F(sys, 0x1B0));
            Mtx_RotateY(mtx, mtx, F(sys, 0x1B4));
            func_00129C50(vel, mtx, vel);
            break;
        case 1:
            Vec4_Set(vel, 0.0f, 0.0f, f, 1.0f);
            Mtx_RotateY(mtx, sys + 0x1D0, F(sys, 0x1B4));
            func_00129C50(vel, mtx, vel);
            break;
        case 2:
            Vec4_Set(vel, 0.0f, f, 0.0f, 1.0f);
            Mtx_RotateY(mtx, sys + 0x1D0, F(sys, 0x1B8));
            func_00129C50(vel, mtx, vel);
            func_00129C50(vel, sys + 0x210, vel);
            func_0012A360(vel, ctx + 0x20, vel, F(cfg, 0xF0) * RF());
            break;
        case 3:
            Vec4_Set(vel, 0.0f, f, 0.0f, 1.0f);
            Mtx_RotateY(mtx, sys + 0x1D0, F(sys, 0x1B8));
            func_00129C50(vel, mtx, vel);
            func_00129C50(vel, sys + 0x170, vel);
            func_0012A360(vel, sys + 0x160, vel, F(cfg, 0xF0) * RF());
            break;
        default:
            break;
        }
        {
            u8 *acc = p + 0xC0;
            switch (cfg[0xB]) {
            case 0:
                Vec3_Sub(acc, ctx + 0x20, dir);
                F(p, 0xCC) = 1.0f;
                Vec3_Normalize(acc, acc);
                Vec3_Scale(acc, acc, F(cfg, 0xD0));
                break;
            case 1:
                Vec3_Normalize(tmp40, vel);
                F(p, 0xCC) = 1.0f;
                Vec3_Sub(acc, ctx + 0x20, tmp40);
                Vec3_Normalize(acc, acc);
                Vec3_Scale(acc, acc, F(cfg, 0xD0));
                break;
            case 2:
                Vec3_Normalize(tmp40, vel);
                Vec3_Add(tmp40, tmp40, dir);
                Vec3_Normalize(tmp40, tmp40);
                Vec3_Sub(acc, ctx + 0x20, tmp40);
                F(p, 0xCC) = 1.0f;
                Vec3_Normalize(acc, acc);
                Vec3_Scale(acc, acc, F(cfg, 0xD0));
                break;
            default:
                break;
            }
        }
        F(p, 0xC4) = F(p, 0xC4) + F(cfg, 0xD4);
        Vec4_Set(p + 0xD0, 0.0f, 1.0f, 0.0f, 1.0f);
        F(p, 0xA0) = F(tb, 0x20) * RF();
        F(p, 0xA4) = F(tb, 0x24) * RF();
        F(p, 0xA8) = F(tb, 0x28) * RF();
        Vec3_Add(p + 0xA0, p + 0xA0, tb + 0x10);
        F(p, 0xAC) = 0.0f;
        F(p, 0xB0) = 0.0f;
        F(p, 0xB4) = 0.0f;
        F(p, 0xB8) = 0.0f;
        f = F(tb, 0x1C) + F(tb, 0x2C) * RF();
        F(p, 0xBC) = f / F(cfg, 0xC8);
        vel = p + 0xB0;
        if (cfg[4] == 0 || (cfg[4] == 1 && (rand() & 1) == 0)) {
            F(p, 0xB0) = F(tb, 0x40) * RF();
            F(p, 0xB4) = F(tb, 0x44) * RF();
            F(p, 0xB8) = F(tb, 0x48) * RF();
            Vec3_Add(vel, vel, tb + 0x30);
            Vec3_Sub(vel, vel, tb + 0x10);
            Vec3_Scale(vel, vel, 1.0f / F(p, 0xC));
        }
        F(p, 0x24) = F(sys, 0xAC) + F(sys, 0xB0) * RF();
        F(p, 0x2C) = F(sys, 0xDC) + F(sys, 0xE0) * RF();
        F(p, 0x34) = F(sys, 0x10C) + F(sys, 0x110) * RF();
        F(p, 0x44) = F(cfg, 0x12C) + F(cfg, 0x130) * RF();
        {
            f32 base = F(cfg, 0x134);
            f32 v = base + F(cfg, 0x138) * RF();
            F(p, 0x48) = v;
            if (*(u32 *)p & 0x20) {
                F(p, 0x48) = -v;
            }
        }
        F(p, 0x24) = F(p, 0x24) * F(ctx, 4);
        F(p, 0x2C) = F(p, 0x2C) * F(ctx, 4);
        F(p, 0x34) = F(p, 0x34) * F(ctx, 4);
        f = (F(sys, 0xB4) + F(sys, 0xB8) * RF()) * F(ctx, 4);
        F(p, 0x28) = (f - F(p, 0x24)) / F(p, 0x10);
        f = (F(sys, 0xE4) + F(sys, 0xE8) * RF()) * F(ctx, 4);
        F(p, 0x30) = (f - F(p, 0x2C)) / F(p, 0x10);
        f = (F(sys, 0x114) + F(sys, 0x118) * RF()) * F(ctx, 4);
        F(p, 0x38) = (f - F(p, 0x34)) / F(p, 0x10);
        Vec4_Scale(vel, vel, 1.0f);
        if (cfg[1] == 1) {
            f32 t = 0.0f;
            f32 x = F(p, 0x24);
            f32 step = F(p, 0x28);
            f32 span = F(p, 0xC) - F(p, 0x10);
            s32 done = 0;
            func_00129C28(tmp50, dir);
            if (0.0f < F(p, 0xC)) {
                do {
                    Vec3_Scale(tmp60, tmp50, x);
                    Vec3_Add(pos, pos, tmp60);
                    if (done != 0) {
                        t = t + 1.0f;
                    } else {
                        s32 hit = F(p, 0x10) <= t;
                        t = t + 1.0f;
                        if (hit) {
                            done = 1;
                            step = ((F(cfg, 0x84) + F(cfg, 0x88) * 0.2999999821f) - x) / span;
                        }
                    }
                    x += step;
                } while (t < F(p, 0xC));
            }
            Vec3_Scale(dir, dir, -1.0f);
        }
        F(sys, 0x258) = F(sys, 0x258) + (F(cfg, 0x60) + F(cfg, 0x64) * RF());
        wrap_angle((f32 *)(sys + 0x258));
        Vec4_Add(sys + 0x1B0, sys + 0x1B0, sys + 0x1C0);
        wrap_angle((f32 *)(sys + 0x1B0));
        wrap_angle((f32 *)(sys + 0x1B4));
        wrap_angle((f32 *)(sys + 0x1B8));
        *(s32 *)(sys + 0x68) += 1;
        count--;
    } while (count > 0);
    return 1;
}
