#include "common.h"

extern u8 *EftAura_AllocSpark(void);
extern s32 rand(void);
extern void func_00129C28(void *arg0, void *arg1);
extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void func_00129C38(void *arg0, void *arg1);
extern void EftAura_GetSparkDirAlt(void *arg0, s32 arg1);
extern void EftAura_GetSparkDir(void *arg0, s32 arg1);
extern void Vec3_Set(void *dst, f32 x, f32 y, f32 z);
extern u8 *D_0038777C;
extern f32 D_003849B8;
extern f32 D_003849BC;
extern f32 D_003849C0;

s32 EftAura_SpawnSpark(u8 *aura, s32 objId, s32 emitter, s32 kind, u8 *offset, f32 follow) {
    u8 sp[0x10];
    u8 *spark;
    u8 *tbl;
    u8 *ent;
    s32 pick;
    s32 flags;
    f32 mag;
    f32 lifeScale;
    f32 r;
    f32 base;
    f32 range;
    f32 div;
    f32 spin;
    f32 spinMul;

    spark = EftAura_AllocSpark();
    pick = rand() % *(s32 *)(aura + 0x1C);
    if (spark == 0) {
        return 0;
    }
    spark[4] = objId;
    *(s32 *)spark = 0;
    if ((*(s32 *)aura & 0x80) != 0) {
        *(s32 *)spark = 8;
    }
    if ((*(s64 *)(aura + 0x10) & 0x18) != 0) {
        *(s32 *)spark |= 0x10;
    }
    if (*(s32 *)(aura + 0x30) == 1) {
        *(s32 *)spark |= 2;
    }
    spark[5] = emitter;
    spark[6] = kind;
    *(s32 *)(spark + 8) = 0;
    if ((*(s32 *)spark & 0x10) != 0) {
        r = (f32)rand();
        div = D_003849B8;
        range = *(f32 *)(D_0038777C + 0x1CC);
        base = *(f32 *)(D_0038777C + 0x1C8);
    } else {
        r = (f32)rand();
        div = D_003849BC;
        range = *(f32 *)(D_0038777C + 0x1C4);
        base = *(f32 *)(D_0038777C + 0x1C0);
    }
    *(f32 *)(spark + 0xC) = base + range * (r / div);
    *(f32 *)(spark + 0x20) = follow;
    func_00129C28(spark + 0x40, offset);
    Vec4_Set(spark + 0x50, 0.0f, 0.0f, 0.0f, 0.0f);
    spark[7] = 1;
    ent = aura + pick * 16;
    if ((*(s32 *)aura & 0x20) == 0) {
        func_00129C38(spark + 0x70, ent + 0x450);
        *(f32 *)(spark + 0x7C) = 0.0f;
        mag = *(f32 *)(ent + 0x45C) * *(f32 *)(aura + 0x4C);
        EftAura_GetSparkDir(sp, objId);
        if ((*(s32 *)spark & 8) != 0) {
            *(s32 *)(spark + 0x18) = *(s32 *)(D_0038777C + 0x1E8);
            lifeScale = *(f32 *)(D_0038777C + 0x1EC);
        } else {
            *(s32 *)(spark + 0x18) = *(s32 *)(D_0038777C + 0x1E0);
            lifeScale = *(f32 *)(D_0038777C + 0x1E4);
        }
    } else {
        func_00129C38(spark + 0x70, ent + 0x490);
        *(f32 *)(spark + 0x7C) = 0.0f;
        mag = *(f32 *)(ent + 0x49C);
        EftAura_GetSparkDirAlt(sp, objId);
        if ((*(s32 *)spark & 8) != 0) {
            *(s32 *)(spark + 0x18) = *(s32 *)(D_0038777C + 0x1F8);
            lifeScale = *(f32 *)(D_0038777C + 0x1FC);
        } else {
            *(s32 *)(spark + 0x18) = *(s32 *)(D_0038777C + 0x1F0);
            lifeScale = *(f32 *)(D_0038777C + 0x1F4);
        }
    }
    *(f32 *)(spark + 0x1C) = lifeScale;
    func_00129C28(spark + 0x60, sp);
    *(f32 *)(spark + 0x6C) = 1.0f;
    Vec3_Set(spark + 0x80, 0.0f, 0.0f, 0.0f);
    *(f32 *)(spark + 0x8C) = mag / *(f32 *)(D_0038777C + 0x1B8);
    Vec4_Set(spark + 0x90, 0.0f, 0.0f, 1.0f, 1.0f);
    *(f32 *)(spark + 0x10) = 0.0f;
    *(f32 *)(spark + 0x14) = *(f32 *)(D_0038777C + 0x1D4) * D_003849C0;
    if ((rand() & 1) != 0) {
        *(f32 *)(spark + 0x14) = -*(f32 *)(spark + 0x14);
    }
    flags = *(s32 *)spark;
    if ((flags & 4) != 0) {
        spin = *(f32 *)(spark + 0x1C);
        *(f32 *)(spark + 0x14) = *(f32 *)(spark + 0x14) * *(f32 *)(D_0038777C + 0x200);
        spinMul = *(f32 *)(D_0038777C + 0x204);
        *(f32 *)(spark + 0x1C) = spin * spinMul;
    } else if ((flags & 2) != 0) {
        spin = *(f32 *)(spark + 0x1C);
        *(f32 *)(spark + 0x14) = *(f32 *)(spark + 0x14) * *(f32 *)(D_0038777C + 0x208);
        spinMul = *(f32 *)(D_0038777C + 0x20C);
        *(f32 *)(spark + 0x1C) = spin * spinMul;
    }
    return 1;
}
