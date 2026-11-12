#include "common.h"

/*
 * Aura flame parameters, 0x179D00..0x17A188 (BT3 src/battle/eft_m.c).
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
/* @lit4 */
extern const f32 D_003849D4; /* 2147483520 */
extern const f32 D_003849D8; /* 2147483520 */
extern const f32 D_003849DC; /* 0.1499999911 */
extern volatile const f32 D_003849E0; /* 0.8499999642 */
extern const f32 D_003849E4; /* 2147483520 */
extern const f32 D_003849E8; /* 2147483520 */


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

/* Flag word of a new flame from the aura's state. */
s32 EftAura_GetFlameFlags(EftAura *aura, s32 objId, u8 second, u8 alt) {
    s32 flags = 0x800;

    if (second == 0) {
        if (alt == 0) {
            flags = 0;
        } else {
            flags = 0x400;
        }
    }
    if (aura->flags & 0x80) {
        flags |= 0x100;
    }
    if (aura->typeMask & 0x18) {
        flags |= 0x200;
    }
    if (aura->burst == 1) {
        flags |= 0x20;
    } else if (aura->burst == 2) {
        flags |= 0x40;
    }
    if (aura->flags & 0x20) {
        flags |= 0x1000;
    }
    return flags;
}

/* Life of a new flame in frames. */
f32 EftAura_GetFlameLife(s32 flags, f32 burst) {
    f32 *p = gEftAuraPrm->life;
    f32 life;

    if (flags & 0x200) {
        life = p[2] + p[2] * RANDF(D_003849D4);
    } else {
        life = p[0] + p[1] * RANDF(D_003849D8);
    }
    if (flags & 0x20) {
        life *= 1.0f - burst * D_003849DC;
    } else if (flags & 0x80) {
        life *= D_003849E0;
    }
    return life;
}

/* Speed of a new flame. */
f32 EftAura_GetFlameSpeed(s32 flags, s32 objId, f32 level, f32 burst) {
    f32 *p = gEftAuraPrm->speed;
    f32 speed;

    speed = (BtlCharApi_GetSpeed(objId) * p[2] + p[0]) * level;
    if (flags & 0x100) {
        if (flags & 0x800) {
            speed += p[3];
        }
    }
    if (flags & 0x80) {
        speed += p[4];
    } else if (flags & 0x20) {
        speed += p[5] * burst;
    }
    if (!(flags & 0x800)) {
        if (flags & 0x400) {
            p = gEftAuraPrm->speedRand[1];
        } else {
            p = gEftAuraPrm->speedRand[0];
        }
    } else {
        p = gEftAuraPrm->speedRand[2];
    }
    return speed * (p[0] + p[1] * RANDF(D_003849E4));
}

/* Peak alpha of a new flame. */
f32 EftAura_GetFlameAlpha(EftAura *aura, s32 flags, f32 alpha) {
    f32 *base = gEftAuraPrm->alpha;
    f32 *mul = gEftAuraPrm->alphaMul;

    if (!(flags & 0x800)) {
        alpha *= base[0];
    } else {
        alpha *= base[1];
    }
    if (flags & 0x80) {
        alpha *= mul[2];
    } else if (flags & 0x20) {
        alpha *= mul[3];
    } else if (!(flags & 0x800)) {
        alpha *= mul[0];
    } else {
        alpha *= mul[1];
    }
    return alpha;
}

/* Stretch of a flame at a phase (0 start, 1 grown, 2 late, 3 end); 0 for an invisible flame. */
f32 EftAura_GetFlameStretch(EftAuraFlame *f, s32 objId, s32 phase) {
    f32 *mul = gEftAuraPrm->stretchMul;
    f32 *kind = gEftAuraPrm->stretchKind;
    f32 *rnd = gEftAuraPrm->stretchRand[f->kind];
    f32 *st = &gEftAuraPrm->stretch[phase];
    f32 v = *st;
    f32 k;

    if (f->flags & 0x1000) {
        return 0.0f;
    }
    if (f->flags & 0x100) {
        if (!(f->flags & 0x800)) {
            v *= kind[2];
        } else {
            v *= kind[3];
        }
    } else if (!(f->flags & 0x800)) {
        v *= kind[0];
    } else {
        v *= kind[1];
    }
    if (f->flags & 0x80) {
        v *= mul[0];
    } else if (f->flags & 0x20) {
        v *= mul[1];
    } else if (f->flags & 0x40) {
        v *= mul[2];
    }
    k = rnd[0] + rnd[1] * RANDF(D_003849E8);
    k += BtlCharApi_GetSpeed(objId) * rnd[2];
    if (1.0f < k) {
        k = 1.0f;
    }
    return v * k;
}

/* Size of a flame at a phase; 0 for an invisible flame. */
f32 EftAura_GetFlameSize(EftAuraFlame *f, s32 objId, s32 phase) {
    f32 v = gEftAuraPrm->size[phase];

    if (f->flags & 0x1000) {
        return 0.0f;
    }
    if (f->flags & 0x100) {
        if (!(f->flags & 0x800)) {
            v *= gEftAuraPrm->sizeKind[2];
        } else {
            v *= gEftAuraPrm->sizeKind[2];
        }
    } else {
        v *= gEftAuraPrm->sizeKind[0];
    }
    if (f->flags & 0x80) {
        v *= gEftAuraPrm->sizeMul[0];
    } else if (f->flags & 0x20) {
        v *= gEftAuraPrm->sizeMul[1];
    } else if (f->flags & 0x40) {
        v *= gEftAuraPrm->sizeMul[2];
    }
    return v;
}
