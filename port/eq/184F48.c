#include "common.h"

s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 Rand_IntRange(s32 lo, s32 hi);
f32 Rand_FloatRange(f32 lo, f32 hi);
void func_00187568(u8 *arg0, f32 fa, f32 fb);
void Vec3_Sub(u8 *a0, u8 *a1, u8 *a2);
void sceVu0DivVectorXYZ(u8 *out, u8 *in, f32 div);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
extern s32 rand();
extern f32 D_00384BA8;

/* 0x00184F48: initialise a particle (dst, 0xC0 bytes) from the emitter ranges in cfg (a1) and the colour ranges
 * in cfg2 (a2). a3 = random index range, t0 = kind byte stored at +0xBC. */
void func_00184F48(u8 *dst, u8 *cfg, f32 *cfg2, u32 a3, u32 t0) {
    u8 *c1 = dst + 0x20;
    u8 *c2 = dst + 0x30;
    s32 canFlip = 1;
    f32 scale = D_00384BA8;
    f32 life;
    f32 r1;
    f32 r2;
    f32 r3;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 lo;
    f32 hi;
    f32 mix;
    f32 sp[8];

    Vec4_Set(dst, 0.0f, 0.0f, 0.0f, 1.0f);
    Vec4_Set(dst + 0x10, 0.0f, 0.0f, 1.0f, 1.0f);
    dst[0xBC] = (u8)t0;
    if ((*(u32 *)(cfg + 0xA4) & 0x2000) != 0) {
        dst[0xBD] = (u8)Rand_IntRange(0, (u8)a3);
    } else {
        dst[0xBD] = 0;
    }
    *(u16 *)(dst + 0xBE) = 0;
    *(f32 *)(dst + 0xB8) = Rand_FloatRange(*(f32 *)(cfg + 0x84), *(f32 *)(cfg + 0x84) + *(f32 *)(cfg + 0x88));
    *(s32 *)(dst + 0xB0) = 0;
    *(f32 *)(dst + 0xB4) = Rand_FloatRange(*(f32 *)(cfg + 0x8C), *(f32 *)(cfg + 0x8C) + *(f32 *)(cfg + 0x90));
    *(f32 *)(dst + 0xA4) = Rand_FloatRange(*(f32 *)(cfg + 8), *(f32 *)(cfg + 8) + *(f32 *)(cfg + 0xC)) * scale;
    *(f32 *)(dst + 0xA8) = Rand_FloatRange(*(f32 *)(cfg + 0x18), *(f32 *)(cfg + 0x18) + *(f32 *)(cfg + 0x1C)) * scale;
    lo = *(f32 *)(cfg + 0x18);
    if (lo < 0.0f && 0.0f < lo + *(f32 *)(cfg + 0x1C)) {
        canFlip = 0;
    }
    if (0.0f < lo && lo + *(f32 *)(cfg + 0x1C) < 0.0f) {
        canFlip = 0;
    }
    if (canFlip != 0 && (*(u32 *)(cfg + 0xA4) & 0x1000) != 0 && (Rand_IntRange(0, 0x400) & 1) == 0) {
        *(f32 *)(dst + 0xA8) = -*(f32 *)(dst + 0xA8);
    }
    r1 = Rand_FloatRange(0.0f, *(f32 *)(cfg + 0x54));
    r2 = Rand_FloatRange(0.0f, *(f32 *)(cfg + 0x58));
    r3 = Rand_FloatRange(0.0f, *(f32 *)(cfg + 0x5C));
    life = *(f32 *)(dst + 0xB8);
    x0 = *(f32 *)(cfg + 0x48) + r1;
    y0 = *(f32 *)(cfg + 0x4C) + r2;
    z0 = *(f32 *)(cfg + 0x50) + r3;
    mix = *(f32 *)(cfg + 0x80);
    *(f32 *)(dst + 0x90) = (y0 - x0) / life * mix;
    *(f32 *)(dst + 0x88) = x0;
    *(f32 *)(dst + 0x94) = (z0 - y0) / life * (1.0f - *(f32 *)(cfg + 0x80));
    x0 = *(f32 *)(cfg + 0x60) + r1;
    y0 = *(f32 *)(cfg + 0x64) + r2;
    z0 = *(f32 *)(cfg + 0x68) + r3;
    mix = *(f32 *)(cfg + 0x80);
    *(f32 *)(dst + 0x98) = (y0 - x0) / life * mix;
    *(f32 *)(dst + 0x8C) = x0;
    *(f32 *)(dst + 0x9C) = (z0 - y0) / life * (1.0f - *(f32 *)(cfg + 0x80));
    *(f32 *)(dst + 0x20) = Rand_FloatRange(cfg2[0], cfg2[0] + cfg2[4]);
    *(f32 *)(dst + 0x24) = Rand_FloatRange(cfg2[1], cfg2[1] + cfg2[5]);
    *(f32 *)(dst + 0x28) = Rand_FloatRange(cfg2[2], cfg2[2] + cfg2[6]);
    *(f32 *)(dst + 0x2C) = 0.0f;
    sp[0] = Rand_FloatRange(cfg2[8], cfg2[8] + cfg2[12]);
    sp[1] = Rand_FloatRange(cfg2[9], cfg2[9] + cfg2[13]);
    sp[2] = Rand_FloatRange(cfg2[10], cfg2[10] + cfg2[14]);
    sp[3] = 0.0f;
    func_00187568(c1, 0.0f, 255.0f);
    func_00187568((u8 *)sp, 0.0f, 255.0f);
    Vec3_Sub(c2, (u8 *)sp, c1);
    sceVu0DivVectorXYZ(c2, c2, *(f32 *)(dst + 0xB8));
    Vec3_Scale(c2, c2, 1.0f);
    life = *(f32 *)(dst + 0xB8);
    *(f32 *)(dst + 0x80) = cfg2[3] / (life * *(f32 *)(cfg + 0x78));
    *(f32 *)(dst + 0x84) = cfg2[3] / (life * (1.0f - *(f32 *)(cfg + 0x78)));
    if ((*(u32 *)(cfg + 0xA4) & 0x80) != 0) {
        *(u16 *)(dst + 0xBE) = *(u16 *)(dst + 0xBE) | 0x100;
    }
    if ((*(u32 *)(cfg + 0xA4) & 0x100) != 0 && (rand() & 1) == 0) {
        *(u16 *)(dst + 0xBE) = *(u16 *)(dst + 0xBE) | 0x100;
    }
}
