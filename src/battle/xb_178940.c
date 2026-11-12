#define func_00129AE8 Vec3_Normalize  /* fix_targets */ /* the original uses 0x129ae8 here */
#include "common.h"

/*
 * Aura particle helpers, 0x178940..0x1791D0 (BT3 src/battle/eft_m.c, same code).
 * BT3 names for the BT2 placeholders this file calls / reads (same code at these addresses).
 */
#define gEftAuraCfg D_0038777C
#define gEftAuraPrm D_00387780
#define Vec3_Normalize func_00129AE8
#define Vec4_Sub func_00129B58
#define Vec3_Sub func_00129B70
#define Vec4_Scale func_00129BB8
#define Vec3_Scale func_00129BD0
#define Vec3_Copy func_00129C38
#define Vec3_Dot func_00129CD8
#define BtlCharApi_GetVelocity func_00208B40
#define BtlCharApi_GetDir func_00208BE0
#define BtlCharApi_GetSpeed func_00208CC8
#define BtlCharApi_GetFallSpeed func_00208D50
#define BtlCharApi_GetActionFxKind func_00209C18

#include "battle/xb_eft_m.h"

/* Float constants (.lit4 of the original object, one word per use; values checked against the data). */
extern const f32 D_00384998; /* 2147483647.0 */
extern const f32 D_0038499C; /* 2147483647.0 */
extern const f32 D_003849A0; /* 2147483647.0 */
extern const f32 D_003849A4; /* 0.1 */
extern const f32 D_003849A8; /* 0.08 */
extern const f32 D_003849AC; /* 0.15 */
extern const f32 D_003849B0; /* 0.2 */
extern const f32 D_003849B4; /* 0.8 */


/* rand() scaled to [0, 1]: the divisor is a 2147483647.0f constant of each use (.lit4, given as the label). */
#define RANDF(k) ((f32)rand() / (k))

typedef struct EftMBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 = paused */
} EftMBattleWork;

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftMView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
} EftMView;

extern EftMView *gBtlCamView;

#define V(p) ((Vec4 *)(p))

extern s32 rand(void);
extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);
extern f32 Mathf_Sin(f32 angle);
extern f32 Mathf_Cos(f32 angle);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Set(Vec4 *dst, f32 x, f32 y, f32 z);  /* sets x, y, z */
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Copy(Vec4 *dst, Vec4 *src);            /* copies x, y, z */
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec4_Clamp(Vec4 *dst, Vec4 *src, f32 lo, f32 hi); /* clamps each component */
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);          /* copy */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);          /* inverse of a rotation + translation matrix */
extern void Vu0Cur_Push(void);                            /* VU0 matrix stack push */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                        /* load the matrix */
extern void Vu0Cur_Pop(void);                            /* pop */
extern void ClipVtx_Set(void *vtx, Vec4 *pos, Vec4 *uv, Vec4 *col);
extern void EftGfx_DrawPolyAvgZFront(void *prim, s32 blend, s32 a2, s32 a3, s32 inView, s32 t1, u64 tex, s32 t3);
extern void EftTexSet_Load4(EftSpdTex *tex, s32 *entry);
extern void EftTexSet_Keep4(EftSpdTex *tex, s32 a, s32 b);
extern EftMBattleWork *Battle_GetWork(void);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern s32 BtlScene_IsCharInView(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern f32 BtlCharApi_GetPartUnk5C(s32 objId, s32 node);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern void BtlCharApi_GetFrameMove(s32 objId, Vec4 *out);
extern void BtlCharApi_GetVelocity(s32 objId, Vec4 *out);
extern void BtlCharApi_GetDir(s32 objId, Vec4 *out);
extern f32 BtlCharApi_GetSpeed(s32 objId);
extern f32 BtlCharApi_GetFallSpeed(s32 objId);
extern s32 BtlCharApi_GetActionFxKind(s32 objId);

/* ---- aura particles ------------------------------------------------------------------------------------- */

extern void EftSpr_DrawRot(u8 r, u8 g, u8 b, u8 a, f32 x, f32 y, f32 z, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot,
                          s32 t0, s32 t1, s32 w, s32 h, s32 s0, u32 size, s32 s2, s32 s3, void *tex);

/* Drift direction of a spark: against the fighter's velocity, with a random vertical part. */
void EftAura_GetSparkDir(Vec4 *out, s32 objId) {
    Vec4 vel;

    BtlCharApi_GetVelocity(objId, &vel);
    Vec4_Scale(&vel, &vel, gEftAuraPrm->sparkVel);
    Vec4_Set(out, -vel.x, gEftAuraPrm->sparkRise * RANDF(D_00384998), -vel.z, 1.0f);
    Vec3_Normalize(out, out);
}

/* The same for the alternate aura: straight up / down while the action effect kind is 3 / 4. */
void EftAura_GetSparkDirAlt(Vec4 *out, s32 objId) {
    Vec4 vel;
    s32 kind;

    BtlCharApi_GetVelocity(objId, &vel);
    Vec4_Scale(&vel, &vel, gEftAuraPrm->sparkVelAlt);
    kind = BtlCharApi_GetActionFxKind(objId);
    if (kind == 3) {
        Vec3_Set(out, 0.0f, 1.0f - BtlCharApi_GetFallSpeed(objId), 0.0f);
    } else if (kind == 4) {
        Vec3_Set(out, 0.0f, -1.0f - BtlCharApi_GetFallSpeed(objId), 0.0f);
    } else {
        Vec3_Set(out, -vel.x, gEftAuraPrm->sparkRise * RANDF(D_0038499C), -vel.z);
    }
    out->w = 1.0f;
    Vec3_Normalize(out, out);
}

/* Flame direction term: away from the aura centre, plus a random left / right push across the facing. */
void EftAura_GetFlameSideDir(EftAura *aura, Vec4 *out, s32 objId, f32 power, f32 away, f32 side) {
    Vec4 dir;
    Vec4 centre;
    f32 one = 1.0f;

    side += gEftAuraCfg->unk1A0 * power * gEftAuraPrm->sideScale;
    BtlCharApi_GetDir(objId, &dir);
    dir.y = 0.0f;
    dir.w = one;
    Vec3_Normalize(&dir, &dir);
    if (rand() & 1) {
        side = -side;
    }
    Vec4_Scale(&dir, &dir, side);
    Vec4_Set(&centre, aura->unk310.x, 0.0f, aura->unk310.z, one);
    Vec3_Sub(out, &centre, &aura->pos);
    out->w = one;
    Vec3_Normalize(out, out);
    Vec3_Scale(out, out, away);
    out->x += dir.x;
    out->z += dir.z;
}

/* Flame direction term: against the motion of the body part relative to the fighter's root. */
void EftAura_GetFlameDragDir(EftAura *aura, Vec4 *pos, Vec4 *out, s32 objId, s32 part) {
    Vec4 d;
    Vec4 now;
    Vec4 before;
    f32 one;

    Vec3_Sub(&now, pos, &aura->pos);
    Vec3_Sub(&before, &aura->partPrev[part], &aura->prevPos);
    Vec3_Sub(&d, &now, &before);
    one = 1.0f;
    d.w = one;
    Vec3_Normalize(&d, &d);
    Vec4_Scale(&d, &d, sqrtf(Vec3_Dot(&d, &d)) * gEftAuraPrm->drag);
    Vec3_Scale(out, &d, -1.0f);
    out->w = one;
}

/* Flame direction term: outward from a random point between the aura axis and the root, scaled down by speed. */
void EftAura_GetFlameOutDir(EftAura *aura, Vec4 *out, s32 objId, s32 part, f32 power, f32 amount) {
    Vec4 from;
    Vec4 span;
    Vec4 d;
    f32 one;
    f32 ratio;
    f32 t;

    ratio = BtlCharApi_GetSpeed(objId) * gEftAuraPrm->speedRef;
    one = 1.0f;
    t = RANDF(D_003849A0);
    amount += gEftAuraCfg->unk1A0 * power;
    if (one < ratio) {
        ratio = one;
    }
    amount *= one - ratio;
    span.x = aura->pos.x - aura->axis.x;
    span.z = aura->pos.z - aura->axis.z;
    from.w = 0.0f;
    from.y = aura->pos.y;
    from.x = aura->axis.x + span.x * t;
    from.z = aura->axis.z + span.z * t;
    Vec3_Copy(&d, &aura->part[part]);
    d.w = 0.0f;
    Vec4_Sub(&d, &d, &from);
    Vec3_Normalize(&d, &d);
    Vec4_Set(out, d.x * amount, d.y * amount * gEftAuraPrm->outRise, d.z * amount, one);
}

/* Bends a flame's direction: early towards its start direction and turn axis, late towards `pos`. */
void EftAura_TurnFlame(EftAuraFlame *f, Vec4 *pos, f32 t) {
    Vec4 d;
    Vec4 tmp;
    f32 t3 = t * t * t;
    f32 one = 1.0f;
    Vec4 *dir = &f->dir;
    f32 turn = gEftAuraPrm->kind[f->kind].turn;

    Vec3_Scale(&tmp, &f->dirStart, (one - t3) * D_003849A4 * turn);
    Vec3_Add(dir, dir, &tmp);
    Vec3_Scale(&tmp, &f->dirTurn, (one - t) * D_003849A8 * turn);
    Vec3_Add(dir, dir, &tmp);
    Vec3_Sub(&d, pos, &f->pos);
    d.w = one;
    Vec3_Normalize(&d, &d);
    Vec3_Scale(&tmp, &d, t3 * D_003849AC * turn);
    Vec3_Add(dir, dir, &tmp);
    f->dir.w = one;
    Vec3_Normalize(dir, dir);
}

/* Accelerates a flame early in its life and damps it later. */
void EftAura_AccelFlame(EftAuraFlame *f, f32 t) {
    f->speed = (f->speed + gEftAuraPrm->speed[1] * (1.0f - t) * gEftAuraPrm->kind[f->kind].accel) * (t * D_003849B0 + D_003849B4);
}

/* Offset from the aura axis (at the root's height) towards a body part. */
void EftAura_GetPartOffset(EftAura *aura, Vec4 *out, s32 objId, s32 part, f32 radial, f32 vertical) {
    Vec4 from;
    Vec4 d;

    from.x = aura->axis.x;
    from.y = aura->pos.y;
    from.z = aura->axis.z;
    from.w = 0.0f;
    Vec3_Copy(&d, &aura->part[part]);
    Vec3_Sub(&d, &d, &from);
    d.w = 1.0f;
    Vec3_Normalize(&d, &d);
    out->w = 0.0f;
    out->x = d.x * radial;
    out->y = d.y * vertical;
    out->z = d.z * radial;
}

/* Takes a spark from the free list, else the next unused slot; links it on the used list. */
EftAuraSpark *EftAura_AllocSpark(void) {
    EftAuraSpark *p;

    if (gEftAuraPool->sparkFree != NULL) {
        p = gEftAuraPool->sparkFree;
        gEftAuraPool->sparkFree = p->next;
    } else if (gEftAuraPool->sparkNext <= gEftAuraPool->sparkMax - 1) {
        p = &gEftAuraPool->sparks[gEftAuraPool->sparkNext++];
    } else {
        return NULL;
    }
    p->next = gEftAuraPool->sparkUsed;
    gEftAuraPool->sparkUsed = p;
    p->flags = 0;
    return p;
}

/* Returns every spark of a fighter to the free list. */
void EftAura_FreeSparks(s32 objId) {
    EftAuraSpark **link = &gEftAuraPool->sparkUsed;
    EftAuraSpark *p;

    while (*link != NULL) {
        p = *link;
        if (p->objId != objId) {
            link = &p->next;
        } else {
            *link = p->next;
            p->next = gEftAuraPool->sparkFree;
            gEftAuraPool->sparkFree = p;
        }
    }
}
