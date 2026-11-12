#include "common.h"

extern void func_00129C28(void *arg0, void *arg1);
extern void func_00129BD0(void *arg0, void *arg1, f32 farg0);
extern void Vec3_Normalize(void *arg0, void *arg1);
extern void EftKiBomb_Reflect(void *out, void *vel, void *normal);
extern f32 EftMath_WrapAngle(f32 farg0);
extern s32 rand(void);
extern u8 D_0036EAF0[16];
extern f32 D_0036EB00[3];
extern f32 D_00384F10;

/* Ki-blast bounce: places the projectile (state at obj+0x38) from the owner position, then on
   hit flags (obj+4: 2/1 = snap to owner, 4/0x10 = bounce) reflects the velocity (+0x70) off the
   surface normal (up to 3 bounces), halves speed and decay, or after the 3rd bounce parks it
   below the owner and picks a random spin from {0, 90, 270} degrees. */
void func_001ACD88(u8 *obj) {
    f32 normal[4];
    f32 ang[3];
    f32 refl[4];
    u8 *st;
    u32 flags;
    f32 *vel;
    f32 d;
    f32 half;
    f32 dist;

    __builtin_memcpy(normal, D_0036EAF0, 16);
    ang[0] = D_0036EB00[0];
    ang[1] = D_0036EB00[1];
    ang[2] = D_0036EB00[2];
    st = *(u8 **)(obj + 0x38);
    if (*(s32 *)(st + 0x11C) == -1) {
        return;
    }
    flags = *(u32 *)(obj + 4);
    if (flags & 2) {
        func_00129C28(st + 0x50, obj + 0x10);
        *(u32 *)(st + 0xC0) = (*(u32 *)(st + 0xC0) | 0x100) & ~0x80u;
        return;
    }
    if (flags & 1) {
        func_00129C28(st + 0x50, obj + 0x10);
        *(u32 *)(st + 0xC0) = *(u32 *)(st + 0xC0) | 0x100;
        return;
    }
    if (!(flags & 0x14)) {
        return;
    }

    vel = (f32 *)(st + 0x70);
    Vec3_Normalize(vel, vel);
    d = *(f32 *)(st + 0xD4);
    *(f32 *)(st + 0x50) = *(f32 *)(obj + 0x10) + (-vel[0] * d);
    *(f32 *)(st + 0x54) = *(f32 *)(obj + 0x14) + (-vel[1] * d);
    *(f32 *)(st + 0x58) = *(f32 *)(obj + 0x18) + (-vel[2] * d);

    if (*(s16 *)(st + 0xE8) < 3) {
        if (*(u32 *)(obj + 4) & 0x10) {
            func_00129BD0(normal, st + 0x50, -1.0f);
            Vec3_Normalize(normal, normal);
        } else {
            func_00129C28(normal, st + 0xB0);
        }
        EftKiBomb_Reflect(refl, vel, normal);
        dist = *(f32 *)(st + 0xD4) + 1.0f;
        half = *(f32 *)(st + 0xCC) * 0.5f;
        *(f32 *)(st + 0xDC) = *(f32 *)(st + 0xDC) * 0.5f;
        *(f32 *)(st + 0xCC) = half;
        *(f32 *)(st + 0x50) = *(f32 *)(obj + 0x10) + normal[0] * dist;
        *(f32 *)(st + 0x54) = *(f32 *)(obj + 0x14) + normal[1] * dist;
        *(f32 *)(st + 0x58) = *(f32 *)(obj + 0x18) + normal[2] * dist;
        vel[0] = refl[0] * half;
        *(f32 *)(st + 0x74) = refl[1] * *(f32 *)(st + 0xCC);
        *(f32 *)(st + 0x78) = refl[2] * *(f32 *)(st + 0xCC);
        *(u16 *)(st + 0xE8) = *(u16 *)(st + 0xE8) + 1;
        flags = *(u32 *)(obj + 4);
        if (flags & 4) {
            flags = flags & ~4u;
            *(u32 *)(obj + 4) = flags;
        }
        if (flags & 0x10) {
            *(u32 *)(obj + 4) = flags & ~0x10u;
        }
    } else {
        u32 sflags;

        *(s32 *)vel = 0;
        *(s32 *)(st + 0x74) = 0;
        *(s32 *)(st + 0x78) = 0;
        *(s32 *)(st + 0xE0) = 0;
        *(s32 *)(st + 0xDC) = 0;
        d = *(f32 *)(st + 0xD4);
        *(f32 *)(st + 0x50) = *(f32 *)(obj + 0x10);
        *(f32 *)(st + 0x54) = *(f32 *)(obj + 0x14) - d;
        *(f32 *)(st + 0x58) = *(f32 *)(obj + 0x18);
        func_00129C28(normal, st + 0xB0);
        d = *(f32 *)(st + 0xD4);
        *(f32 *)(st + 0x50) = *(f32 *)(obj + 0x10) + normal[0] * d;
        sflags = *(u32 *)(st + 0xC0);
        *(f32 *)(st + 0x54) = *(f32 *)(obj + 0x14) + normal[1] * d;
        *(f32 *)(st + 0x58) = *(f32 *)(obj + 0x18) + normal[2] * d;
        if (!(sflags & 0x200)) {
            s32 pick = rand() % 3;

            *(f32 *)(st + 0xD8) = EftMath_WrapAngle(ang[pick] / 180.0f * D_00384F10);
            *(u32 *)(obj + 4) = *(u32 *)(obj + 4) & ~4u;
            sflags = *(u32 *)(st + 0xC0);
        }
        *(u32 *)(st + 0xC0) = sflags | 0x200;
    }
}
