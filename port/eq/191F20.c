#include "common.h"

extern f32 D_00384C48;
extern f32 D_00384C4C;
extern f32 D_00384C50;
extern f32 D_00384C54;
extern f32 D_00384C58;
extern f32 D_00384C5C;
extern f32 D_00384C60;

extern s32 rand(void);
extern u8 *func_00191A60(u8 *obj);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Mtx_RotateZ(f32 ang, void *a0, void *a1);
extern void Mtx_RotateX(f32 ang, void *a0, void *a1);
extern void Mtx_MulVec4(void *dst, void *mtx, void *vec);
extern void Vec3_Cross(void *dst, void *a, void *b);
extern void Vec3_Normalize(void *dst, void *src);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Scale(void *dst, void *src, f32 s);
extern void Vec4_Scale(f32 s, void *dst, void *src);

/* value = r[0] + r[1] * (rand / div) */
#define RAND_LERP(r, div) ((r)[0] + (r)[1] * ((f32)rand() / (div)))

/* Particle spawner: creates (s32)count particles in obj, each with random position/velocity/rotation. */
s32 func_00191F20(u8 *obj, u8 *src, f32 count) {
    u8 mtx[0x40];
    u8 tmp[0x10];
    f32 *rngLife = (f32 *)(obj + 0x80);
    f32 *rngPos = (f32 *)(obj + 0x78);
    f32 *rngB = (f32 *)(obj + 0x8C);
    f32 *rngC = (f32 *)(obj + 0xA4);
    f32 *rngD = (f32 *)(obj + 0xBC);
    f32 *rngE = (f32 *)(obj + 0xD4);
    f32 *rngF = (f32 *)(obj + 0xE0);
    f32 *rngG = (f32 *)(obj + 0xE4);
    f32 *rngH = (f32 *)(obj + 0xEC);
    f32 *rngI = (f32 *)(obj + 0xF4);
    u8 *desc = *(u8 **)(src + 0x38);
    u8 *shape = *(u8 **)(src + 0x3C);
    s32 n = (s32)count;
    f32 step = D_00384C48 / count;
    f32 angle = 0.0f;
    u8 *p;

    while (n > 0) {
        f32 *q;
        u8 *dir;
        f32 life;
        f32 a;
        f32 d;
        u8 *v;

        p = func_00191A60(obj);
        if (p == 0) {
            return 0;
        }
        *(u32 *)p |= 1;
        d = D_00384C58;
        *(f32 *)(p + 0x8) = 0.0f;
        life = (rngLife[0] + rngLife[1] * ((f32)rand() / d)) * 30.0f;
        *(f32 *)(p + 0xC) = life;
        *(f32 *)(p + 0x10) = life * rngLife[2];
        *(f32 *)(p + 0x18) = 0.0f;
        *(f32 *)(p + 0x14) = life - *(f32 *)(desc + 0x10);
        *(f32 *)(p + 0x1C) = rngE[2] * 30.0f;
        if (desc[5] == 1) {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x1C) * ((f32)rand() / d);
        }
        *(f32 *)(p + 0x20) = rngE[1] - rngE[0];
        p[4] = desc[9];
        if (desc[7] == 0) {
            p[5] = 0;
        } else if (desc[7] == 1) {
            p[5] = rand() % *(s32 *)(obj + 0x1BC);
        }
        if (!(*(u32 *)(obj + 0x60) & 0x20)) {
            *(u32 *)(p + 0x130) = 0;
            *(f32 *)(p + 0x134) = 1.0f;
            *(u32 *)(p + 0x138) = 0;
            *(f32 *)(p + 0x13C) = 1.0f;
        }

        /* direction at +0x60 */
        *(f32 *)(p + 0x5C) = RAND_LERP(rngPos, D_00384C4C);
        a = *(f32 *)(p + 0x5C) * *(f32 *)(src + 4);
        Vec4_Set(p + 0x60, 0.0f, -a, 0.0f, 1.0f);
        *(f32 *)(p + 0x5C) = a;
        Vec4_Set(p + 0x70, 0.0f, 0.0f, 0.0f, 1.0f);

        a = angle + step * ((f32)rand() / D_00384C4C);
        *(f32 *)(p + 0x48) = a;
        if (D_00384C50 < a) {
            *(f32 *)(p + 0x48) = a - D_00384C48;
        } else if (a < D_00384C54) {
            *(f32 *)(p + 0x48) = a + D_00384C48;
        }

        a = RAND_LERP(rngH, D_00384C4C);
        *(f32 *)(p + 0x4C) = a;
        if (D_00384C50 < a) {
            *(f32 *)(p + 0x4C) = a - D_00384C48;
        } else if (a < D_00384C54) {
            *(f32 *)(p + 0x4C) = a + D_00384C48;
        }
        Mtx_RotateZ(*(f32 *)(p + 0x48), mtx, obj + 0x130);
        Mtx_MulVec4(p + 0x60, mtx, p + 0x60);
        if (desc[1] == 0) {
            Mtx_MulVec4(p + 0x60, obj + 0x170, p + 0x60);
        }
        angle = angle + step;
        if (D_00384C50 < angle) {
            angle = angle - D_00384C48;
        } else if (angle < D_00384C54) {
            angle = angle + D_00384C48;
        }

        /* up vector at +0xA0 */
        Vec4_Set(p + 0xA0, 0.0f, 0.0f, 1.0f, 1.0f);
        a = RAND_LERP(rngG, D_00384C4C);
        *(f32 *)(p + 0x44) = a;
        if (D_00384C50 < a) {
            *(f32 *)(p + 0x44) = a - D_00384C48;
        } else if (a < D_00384C54) {
            *(f32 *)(p + 0x44) = a + D_00384C48;
        }
        Mtx_RotateX(*(f32 *)(p + 0x44), mtx, obj + 0x130);
        Mtx_RotateZ(*(f32 *)(p + 0x48), mtx, mtx);
        Mtx_MulVec4(p + 0xA0, mtx, p + 0xA0);
        Mtx_MulVec4(p + 0xA0, obj + 0x170, p + 0xA0);
        Vec4_Set(p + 0xB0, 0.0f, 0.0f, 0.0f, 1.0f);
        Vec3_Cross(p + 0xD0, p + 0x60, p + 0xA0);
        Vec3_Normalize(p + 0xD0, p + 0xD0);
        Vec3_Normalize(tmp, p + 0x60);
        Vec3_Sub(p + 0x100, src + 0x20, tmp);
        *(f32 *)(p + 0x10C) = 1.0f;
        Vec3_Normalize(p + 0x100, p + 0x100);
        Vec3_Scale(p + 0x100, p + 0x100, rngF[0]);

        dir = p + 0x120;
        if (desc[8] == 3) {
            s32 idx = rand() % 5;
            s32 off = idx << 4;
            u8 *ent = shape + off;
            *(f32 *)(p + 0x110) = *(f32 *)(ent + 0xA0) * ((f32)rand() / D_00384C4C);
            *(f32 *)(p + 0x114) = *(f32 *)(ent + 0xA4) * ((f32)rand() / D_00384C4C);
            *(f32 *)(p + 0x118) = *(f32 *)(ent + 0xA8) * ((f32)rand() / D_00384C4C);
            Vec3_Add(p + 0x110, p + 0x110, ent + 0x50);
            *(f32 *)(p + 0x11C) = 0.0f;
            *(f32 *)(p + 0x120) = 0.0f;
            *(f32 *)(p + 0x124) = 0.0f;
            *(f32 *)(p + 0x128) = 0.0f;
            *(f32 *)(p + 0x12C) = (*(f32 *)(ent + 0x5C) + *(f32 *)(ent + 0xAC) * ((f32)rand() / D_00384C4C)) / *(f32 *)(desc + 0xC);
        } else {
            f32 dv = D_00384C5C;
            u8 *s10 = shape + 0x10;
            *(f32 *)(p + 0x110) = *(f32 *)(shape + 0x20) * ((f32)rand() / dv);
            *(f32 *)(p + 0x114) = *(f32 *)(shape + 0x24) * ((f32)rand() / dv);
            *(f32 *)(p + 0x118) = *(f32 *)(shape + 0x28) * ((f32)rand() / dv);
            Vec3_Add(p + 0x110, p + 0x110, s10);
            *(f32 *)(p + 0x11C) = 0.0f;
            *(f32 *)(p + 0x120) = 0.0f;
            *(f32 *)(p + 0x124) = 0.0f;
            *(f32 *)(p + 0x128) = 0.0f;
            *(f32 *)(p + 0x12C) = (*(f32 *)(shape + 0x1C) + *(f32 *)(shape + 0x2C) * ((f32)rand() / dv)) / *(f32 *)(desc + 0xC);
            if (desc[8] == 0 || (desc[8] == 1 && (rand() & 1) == 0)) {
                *(f32 *)(p + 0x120) = *(f32 *)(shape + 0x40) * ((f32)rand() / dv);
                *(f32 *)(p + 0x124) = *(f32 *)(shape + 0x44) * ((f32)rand() / dv);
                *(f32 *)(p + 0x128) = *(f32 *)(shape + 0x48) * ((f32)rand() / dv);
                Vec3_Add(dir, dir, shape + 0x30);
                Vec3_Sub(dir, dir, s10);
                Vec3_Scale(dir, dir, 1.0f / *(f32 *)(p + 0xC));
            }
        }

        /* per-particle motion ranges */
        d = D_00384C60;
        *(f32 *)(p + 0x24) = RAND_LERP(rngB, d);
        *(f32 *)(p + 0x2C) = RAND_LERP(rngC, d);
        *(f32 *)(p + 0x34) = RAND_LERP(rngD, d);
        *(f32 *)(p + 0x50) = RAND_LERP(rngI, d);
        a = rngI[2] + rngI[3] * ((f32)rand() / d);
        *(f32 *)(p + 0x54) = a;
        if (*(u32 *)p & 0x20) {
            *(f32 *)(p + 0x54) = -a;
        }
        n--;
        *(f32 *)(p + 0x24) = *(f32 *)(p + 0x24) * *(f32 *)(src + 4);
        *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x2C) * *(f32 *)(src + 4);
        *(f32 *)(p + 0x34) = *(f32 *)(p + 0x34) * *(f32 *)(src + 4);
        *(f32 *)(p + 0x28) = ((rngB[2] + rngB[3] * ((f32)rand() / d)) * *(f32 *)(src + 4) - *(f32 *)(p + 0x24)) / *(f32 *)(p + 0x10);
        *(f32 *)(p + 0x30) = ((rngC[2] + rngC[3] * ((f32)rand() / d)) * *(f32 *)(src + 4) - *(f32 *)(p + 0x2C)) / *(f32 *)(p + 0x10);
        *(f32 *)(p + 0x38) = ((rngD[2] + rngD[3] * ((f32)rand() / d)) * *(f32 *)(src + 4) - *(f32 *)(p + 0x34)) / *(f32 *)(p + 0x10);
        Vec4_Scale(1.0f, dir, dir);
        *(s32 *)(obj + 0x68) += 1;
    }
    return 1;
}
