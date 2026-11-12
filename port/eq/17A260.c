#include "common.h"

extern u8 *gEftAuraPrm;
extern u8 *D_0038777C;
extern f32 D_003849F8;
extern f32 D_003849FC;
extern f32 D_00384A00;

extern u8 *EftAura_AllocFlame(void);
extern s32 rand(void);
extern s32 EftAura_GetFlameFlags(u8 *aura, s32 objId, s32 second, s32 alt);
extern f32 EftAura_GetFlameLife(s32 flags, f32 burst);
extern f32 EftAura_GetFlameSpeed(s32 flags, s32 objId, f32 level, f32 burst);
extern f32 EftAura_GetFlameSize(u8 *f, s32 objId, s32 which);
extern f32 EftAura_GetFlameStretch(u8 *f, s32 objId, s32 which);
extern f32 EftAura_GetFlameEnd(u8 *f, s32 objId);
extern void EftAura_GetSparkDir(u8 *dir, s32 objId);
extern void EftAura_GetFlameDragDir(u8 *aura, u8 *pos, u8 *drag, s32 objId, s32 part);
extern f32 EftAura_GetFlameAlpha(u8 *aura, s32 flags, f32 a);
extern void EftAura_GetFlameSideDir(u8 *aura, u8 *side, s32 objId, f32 power, f32 r1, f32 r2);
extern void EftAura_GetFlameOutDir(u8 *aura, u8 *out, s32 objId, s32 part, f32 power, f32 r3);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void func_00129B58(u8 *dst, u8 *a, u8 *b);
extern void func_00129B28(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);

/* Creates one flame particle of the aura at a body part; returns 0 when no flame slot is free.
   `second` makes the extra flame (kind 2, flag 0x800 colour path). */
s32 EftAura_SpawnFlame(u8 *aura, s32 objId, s32 part, u8 *pos, u8 *offset, f32 follow, u32 alt, u32 second) {
    u8 dir[0x10];
    u8 side[0x10];
    u8 drag[0x10];
    u8 out[0x10];
    u8 d[0x10];
    u8 *f;
    u8 *kind;
    s32 color;
    f32 lifeScale, level, burst, grow, life;
    f32 r1, r2, r3;
    f32 alpha;
    u32 flags;

    alt &= 0xFF;
    second &= 0xFF;
    f = EftAura_AllocFlame();
    __builtin_memset(side, 0, 0x10);
    __builtin_memset(drag, 0, 0x10);
    __builtin_memset(out, 0, 0x10);
    color = rand() % *(s32 *)(aura + 0x1C);
    if (f == 0) {
        return 0;
    }
    lifeScale = *(f32 *)(aura + 0x48);
    level = *(f32 *)(aura + 0x4C);
    burst = *(f32 *)(aura + 0x50);
    f[7] = (u8)objId;
    f[9] = (u8)part;
    f[8] = D_0038777C[part * 12 + 0x410];
    flags = EftAura_GetFlameFlags(aura, objId, second, alt);
    *(u32 *)f = flags;
    if (second != 0) {
        f[4] = 1;
        f[5] = 2;
    } else {
        f[4] = 0;
        f[5] = (flags & 0x400) != 0;
    }
    life = EftAura_GetFlameLife(*(u32 *)f, burst);
    *(f32 *)(f + 0x14) = life;
    *(f32 *)(f + 0x10) = life;
    func_00129C28(f + 0x40, offset);
    *(f32 *)(f + 0x34) = follow;
    *(f32 *)(f + 0x30) = EftAura_GetFlameSpeed(*(u32 *)f, objId, level, burst);
    *(f32 *)(f + 0x38) = lifeScale * burst;
    *(f32 *)(f + 0x18) = *(f32 *)(aura + 0x64) * level;
    *(f32 *)(f + 0x1C) = EftAura_GetFlameSize(f, objId, 0);
    *(f32 *)(f + 0x20) = EftAura_GetFlameStretch(f, objId, 0);
    grow = *(f32 *)(f + 0x14) * *(f32 *)(gEftAuraPrm + 4);
    *(f32 *)(f + 0x24) = (EftAura_GetFlameSize(f, objId, 1) - *(f32 *)(f + 0x1C)) / grow;
    *(f32 *)(f + 0x28) = (EftAura_GetFlameStretch(f, objId, 1) - *(f32 *)(f + 0x20)) / grow;
    *(f32 *)(f + 0x2C) = EftAura_GetFlameEnd(f, objId);
    EftAura_GetSparkDir(dir, objId);
    EftAura_GetFlameDragDir(aura, pos, drag, objId, part);
    if ((*(u32 *)f & 0x100) != 0) {
        f[6] = (u8)(rand() % *(s32 *)(aura + 0x24));
    }
    if ((*(u32 *)f & 0x800) == 0) {
        f[0xB] = 0;
        func_00129BD0(f + 0x60, aura + 0x3F0, ((f32)rand() / D_003849F8) * D_003849FC + 1.0f);
        *(u32 *)(f + 0x6C) = 0;
        func_00129B58(d, aura + 0x400, f + 0x60);
        func_00129BD0(f + 0x70, d, 1.0f / *(f32 *)(f + 0x14));
        alpha = EftAura_GetFlameAlpha(aura, *(u32 *)f, *(f32 *)(aura + 0x3FC));
    } else {
        u8 *alt_col = aura + color * 16 + 0x410;
        f[0xB] = 1;
        func_00129BD0(f + 0x60, alt_col, 1.0f);
        *(u32 *)(f + 0x6C) = 0;
        func_00129B58(d, alt_col, f + 0x60);
        func_00129BD0(f + 0x70, d, 1.0f / *(f32 *)(f + 0x14));
        alpha = EftAura_GetFlameAlpha(aura, *(u32 *)f, *(f32 *)(aura + color * 16 + 0x41C));
    }
    *(f32 *)(f + 0x7C) = alpha * level / *(f32 *)(gEftAuraPrm + 0x2C);
    kind = gEftAuraPrm + f[5] * 32 + 0x104;
    r1 = *(f32 *)(kind + 0) + *(f32 *)(kind + 4) * ((f32)rand() / D_00384A00);
    r2 = *(f32 *)(kind + 8) + *(f32 *)(kind + 0xC) * ((f32)rand() / D_00384A00);
    r3 = *(f32 *)(kind + 0x10) + *(f32 *)(kind + 0x14) * ((f32)rand() / D_00384A00);
    EftAura_GetFlameSideDir(aura, side, objId, *(f32 *)(f + 0x38), r1, r2);
    EftAura_GetFlameOutDir(aura, out, objId, f[9], *(f32 *)(f + 0x38), r3);
    func_00129B28(f + 0xA0, dir, drag);
    Vec3_Normalize(f + 0xA0, f + 0xA0);
    func_00129B28(dir, dir, side);
    func_00129B28(dir, dir, drag);
    Vec3_Normalize(dir, dir);
    func_00129B28(f + 0x80, out, dir);
    Vec3_Normalize(f + 0x80, f + 0x80);
    func_00129C28(f + 0x90, f + 0x80);
    func_00129B58(f + 0xA0, f + 0x80, f + 0xA0);
    Vec3_Normalize(f + 0xA0, f + 0xA0);
    func_00129BD0(f + 0xB0, f + 0x80, *(f32 *)(gEftAuraPrm + 8));
    func_00129B28(f + 0x50, pos, offset);
    func_00129B28(f + 0x50, f + 0x50, f + 0xB0);
    *(f32 *)(f + 0x5C) = 1.0f;
    *(f32 *)(f + 0xC) = *(f32 *)(f + 0x14) * *(f32 *)gEftAuraPrm;
    f[0xA] = (u8)(rand() % 2);
    return 1;
}
