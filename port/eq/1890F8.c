#include "common.h"

extern f32 D_00384BE0;
extern s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern f32 Rand_FloatRange(f32 lo, f32 hi);
extern s32 Rand_IntRange(s32 lo, s32 hi);
extern void func_0018B880(u8 *arg0, f32 fa, f32 fb);
extern void Vec3_Sub(void *arg0, void *arg1, void *arg2);
extern void sceVu0DivVectorXYZ(u8 *out, u8 *in, f32 div);
extern void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
extern s32 rand(void);

#define FP(p, o) (*(f32 *)((p) + (o)))

/* Init one particle (ent) from emitter params (em) and a velocity/direction block (vel). */
void func_001890F8(u8 *ent, u8 *em, u8 *vel, u8 count, u8 flag) {
    u8 sp[0x20];
    s32 ok;
    f32 scale, life, r0, r1, r2, a, b, c, v, e, g;
    u32 flags;

    Vec4_Set(ent, 0.0f, 0.0f, 0.0f, 1.0f);
    Vec4_Set(ent + 0x10, 0.0f, 0.0f, 1.0f, 1.0f);
    *(u8 *)(ent + 0xBC) = flag;
    if (*(u32 *)(em + 0xA4) & 0x2000) {
        *(u8 *)(ent + 0xBD) = Rand_IntRange(0, count);
    } else {
        *(u8 *)(ent + 0xBD) = 0;
    }
    *(u16 *)(ent + 0xBE) = 0;
    ok = 1;
    scale = D_00384BE0;
    v = Rand_FloatRange(FP(em, 0x84), FP(em, 0x84) + FP(em, 0x88));
    *(u32 *)(ent + 0xB0) = 0;
    FP(ent, 0xB8) = v;
    v = Rand_FloatRange(FP(em, 0x8C), FP(em, 0x8C) + FP(em, 0x90));
    FP(ent, 0xB4) = v;
    v = Rand_FloatRange(FP(em, 0x08), FP(em, 0x08) + FP(em, 0x0C));
    FP(ent, 0xA4) = v * scale;
    v = Rand_FloatRange(FP(em, 0x18), FP(em, 0x18) + FP(em, 0x1C));
    FP(ent, 0xA8) = v * scale;
    a = FP(em, 0x18);
    if (a < 0.0f) {
        if (0.0f < a + FP(em, 0x1C)) {
            ok = 0;
        }
    }
    if (0.0f < a) {
        if (a + FP(em, 0x1C) < 0.0f) {
            ok = 0;
        }
    }
    if (ok && (*(u32 *)(em + 0xA4) & 0x1000)) {
        if ((Rand_IntRange(0, 0x400) & 1) == 0) {
            FP(ent, 0xA8) = -FP(ent, 0xA8);
        }
    }

    r0 = Rand_FloatRange(0.0f, FP(em, 0x54));
    r1 = Rand_FloatRange(0.0f, FP(em, 0x58));
    r2 = Rand_FloatRange(0.0f, FP(em, 0x5C));
    life = FP(ent, 0xB8);
    a = FP(em, 0x48) + r0;
    b = FP(em, 0x4C) + r1;
    c = FP(em, 0x50) + r2;
    FP(ent, 0x90) = ((b - a) / life) * FP(em, 0x80);
    FP(ent, 0x88) = a;
    FP(ent, 0x94) = ((c - b) / life) * (1.0f - FP(em, 0x80));
    a = FP(em, 0x60) + r0;
    b = FP(em, 0x64) + r1;
    c = FP(em, 0x68) + r2;
    FP(sp, 0x00) = a;
    FP(sp, 0x04) = b;
    FP(sp, 0x08) = c;
    FP(ent, 0x98) = ((b - a) / life) * FP(em, 0x80);
    FP(ent, 0x8C) = a;
    FP(ent, 0x9C) = ((c - b) / life) * (1.0f - FP(em, 0x80));

    v = Rand_FloatRange(FP(vel, 0x00), FP(vel, 0x00) + FP(vel, 0x10));
    FP(ent, 0x20) = v;
    v = Rand_FloatRange(FP(vel, 0x04), FP(vel, 0x04) + FP(vel, 0x14));
    FP(ent, 0x24) = v;
    v = Rand_FloatRange(FP(vel, 0x08), FP(vel, 0x08) + FP(vel, 0x18));
    FP(ent, 0x2C) = 0.0f;
    FP(ent, 0x28) = v;
    v = Rand_FloatRange(FP(vel, 0x20), FP(vel, 0x20) + FP(vel, 0x30));
    FP(sp, 0x00) = v;
    v = Rand_FloatRange(FP(vel, 0x24), FP(vel, 0x24) + FP(vel, 0x34));
    FP(sp, 0x04) = v;
    v = Rand_FloatRange(FP(vel, 0x28), FP(vel, 0x28) + FP(vel, 0x38));
    FP(sp, 0x08) = v;
    FP(sp, 0x0C) = 0.0f;
    func_0018B880(ent + 0x20, 0.0f, 255.0f);
    func_0018B880(sp, 0.0f, 255.0f);
    Vec3_Sub(ent + 0x30, sp, ent + 0x20);
    sceVu0DivVectorXYZ(ent + 0x30, ent + 0x30, FP(ent, 0xB8));
    Vec3_Scale(ent + 0x30, ent + 0x30, 1.0f);

    e = Rand_FloatRange(FP(vel, 0x0C), FP(vel, 0x0C) + FP(vel, 0x1C));
    if (255.0f < e) {
        e = 255.0f;
    }
    life = FP(ent, 0xB8);
    FP(ent, 0x80) = e / (life * FP(em, 0x78));
    g = 1.0f - FP(em, 0x7C);
    FP(ent, 0x84) = e / (life * g);

    flags = *(u32 *)(em + 0xA4);
    if (flags & 0x80) {
        *(u16 *)(ent + 0xBE) |= 0x100;
        flags = *(u32 *)(em + 0xA4);
    }
    if (flags & 0x100) {
        if ((rand() & 1) == 0) {
            *(u16 *)(ent + 0xBE) |= 0x100;
        }
    }
}
