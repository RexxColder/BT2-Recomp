#include "common.h"
#include "sys/gfx_ot.h"
#include "battle/eft_x.h"

/*
 * Effect tasks, 0x18D618..0x190CC8: the second half of the particle emitter module of effect pack part
 * kind 10 (the first half, 0x18C190..0x18D618, is the end of eft_w.c). See include/battle/eft_x.h.
 * Nothing here touches a fighter, a hit record or a battle object: the module only builds draw packets.
 * Random draws: EftPart10_InitPtcl, per spawned particle: 18 Rand_FloatRange (VU0 generator; only 3 when the
 * life comes out as 0), up to two libc rand() coin flips (definition flag 4, definition byte 0x20D == 2) and
 * one Rand_IntRange (libc rand(); definition flag 0x10, the texture frame). EftPart10_InitSpin, once per
 * emitter with definition flag 0x40: 3 or 9 Rand_FloatRange. They reach only particle appearance.
 *
 * The key-frame functions (EftPart10_StartKeys, EftPart10_UpdateKeys, EftPart10_SetKey) depend on the element
 * type of the definition's two-value tracks: `f32 track[3][2]` (a 2-D array, [key][0 / 1]), not an array of
 * two-float structures. With the structure the second value is addressed as (def + rest + 4) + index, with the
 * 2-D array as (def + rest) + (index + 4), which shares its base with the first value; that one difference
 * changed the allocation of all fifty shared addresses.
 */

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftXView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
    /* 0x180 */ u8 unk180[0xB4];
    /* 0x234 */ f32 screenDist;
} EftXView;

/* One vertex as ClipVtx_Set builds it for the EftGfx_DrawPoly functions. */
typedef struct EftXVert {
    /* 0x00 */ Vec4 pos;
    /* 0x10 */ Vec4 uv;
    /* 0x20 */ Vec4 color;
} EftXVert; /* 0x30 */

/* GS registers of the packets queued here. */
typedef struct EftXXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftXXyzf;

typedef struct EftXRgbaq {
    u8 r, g, b, a;
    f32 q;
} EftXRgbaq;

typedef struct EftXSt {
    f32 s, t;
} EftXSt;

/* DMA tag + REGLIST GIF tag: PRIM, TEX0, four (RGBAQ, ST, XYZF2): a gouraud textured strip. */
typedef struct EftXStripPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000008 */
    /* 0x04 */ struct EftXStripPkt *next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;         /* 0x50000008 */
    /* 0x10 */ u64 gifTag;       /* 0xE400000000008001 */
    /* 0x18 */ u64 regs;         /* 0x42142142142160 */
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    struct {
        /* 0x00 */ EftXRgbaq rgbaq;
        /* 0x08 */ EftXSt st;
        /* 0x10 */ EftXXyzf xyz;
    } v[4];
} EftXStripPkt; /* 0x90 */

/* DMA tag + REGLIST GIF tag: PRIM, TEX0, RGBAQ, four (ST, XYZF2), NOP: a flat textured strip. */
typedef struct EftXQuadPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000007 */
    /* 0x04 */ struct EftXQuadPkt *next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;         /* 0x50000007 */
    /* 0x10 */ u64 gifTag;       /* 0xC400000000008001 */
    /* 0x18 */ u64 regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftXRgbaq rgbaq;
    /* 0x38 */ EftXSt st0;
    /* 0x40 */ EftXXyzf xyz0;
    /* 0x48 */ EftXSt st1;
    /* 0x50 */ EftXXyzf xyz1;
    /* 0x58 */ EftXSt st2;
    /* 0x60 */ EftXXyzf xyz2;
    /* 0x68 */ EftXSt st3;
    /* 0x70 */ EftXXyzf xyz3;
    /* 0x78 */ u64 nop;
} EftXQuadPkt; /* 0x80 */

#define V(p) ((Vec4 *)(p))

/* TEX0 of entry i of a texture table. Only the explicit shift reproduces the original operand order. */
#define EFT_X_TEX0(tex, i) (*(u64 *)((u32)(tex) + ((i) << 4)))

extern EftPart10Mgr *gEftPart10Mgr;
extern EftXView *gBtlCamView;
extern void *gEftPart10Class[6];

extern s32 rand(void);
extern void *memset(void *dst, s32 c, u32 n);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern f32 Mathf_Asin(f32 x);
extern f32 Rand_FloatRange(f32 a, f32 b);
extern s32 Rand_IntRange(s32 a, s32 b);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Vec4_Clamp(Vec4 *dst, Vec4 *src, f32 lo, f32 hi); /* clamps each component */
extern void Vec4_Mul(Vec4 *dst, Vec4 *a, Vec4 *b);          /* per-component product */
extern void Vec4_ToInt(EftXIVec *dst, Vec4 *src);             /* float vector to integer vector */
extern void Mtx_Translate(Mtx44 *dst, Mtx44 *src, Vec4 *v);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);       /* matrix product */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);               /* inverse of a rotation + translation matrix */
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle);    /* rotate about Z */
extern void Vu0Cur_LoadIdentity(void);                                 /* VU0: current matrix = identity */
extern void Vu0Cur_Push(void);                                 /* VU0: push the current matrix */
extern void Vu0Cur_Pop(void);                                 /* VU0: pop */
extern void Vu0Cur_Translate(Vec4 *v);                              /* VU0: translate the current matrix */
extern void Vu0Cur_RotateZ(f32 angle);                            /* VU0: rotate the current matrix (Z) */
extern void Vu0Cur_RotateX(f32 angle);                            /* VU0: rotate (X) */
extern void Vu0Cur_RotateY(f32 angle);                            /* VU0: rotate (Y) */
extern void Vu0Cur_ScaleDiagUniform(f32 scale);                            /* VU0: scale the current matrix */
extern void Vu0Cur_MulVec4(Vec4 *dst, Vec4 *src);                 /* VU0: transform by the current matrix */
extern s32 Vu0Cur_ProjectPoint(EftXIVec *out, Vec4 *pos);              /* project one point with the loaded matrix */
extern s32 Vu0Cur_ProjectPointsStq(EftXIVec *xyz, Vec4 *stq, Vec4 *pos, Vec4 *uv, s32 n); /* project n points; 0 = clipped */
extern void ClipVtx_Set(EftXVert *out, Vec4 *pos, Vec4 *uv, Vec4 *color);
extern f32 EftMath_WrapAngle(f32 angle);
extern void EftGfx_DrawPolyFixedZ(EftXVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex, s32 z);
extern void EftGfx_DrawPolyScaledZ(EftXVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex,
                                   f32 zScale);
extern u64 EftVram_AddImage(EftXTexEntry *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftXTexEntry *tex);
extern EftXTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void EftPart10_Update(EftXTask *task);                       /* the emitter class's update */

s32 EftPart10_InitPtcl(EftPart10Ptcl *p, EftPart10 *em);
void EftPart10_LinkPtcl(EftPart10Ptcl **head, EftPart10Ptcl **tail, EftPart10Ptcl *p);
void EftPart10_SelectTex(EftPart10 *em, EftXTexEntry *tbl, s32 a, s32 b);
s32 EftPart10_IsCornerOffScreen(s32 x, s32 y, s32 z);

/* Appends a burst group to an emitter's list. */
void EftPart10_LinkGroup(EftPart10Group **head, EftPart10Group **tail, EftPart10Group *g) {
    if (*head == NULL) {
        *head = g;
        *tail = g;
    } else {
        g->prev = *tail;
        (*tail)->next = g;
        *tail = g;
    }
}

/* Removes a burst group from an emitter's list. */
void EftPart10_UnlinkGroup(EftPart10Group **head, EftPart10Group **tail, EftPart10Group *p) {
    EftPart10Group *prev;
    EftPart10Group *a; /* one variable for the list head and later for a neighbour: needed for the registers */
    EftPart10Group *b;

    a = *head;
    if (a == NULL) {
        return;
    }
    prev = p->prev;
    if (prev == NULL) {
        p = p->next;
        if (p == NULL) {
            *head = NULL;
            *tail = NULL;
        } else {
            *head = p;
            p->prev = NULL;
        }
    } else {
        a = p->next;
        if (a == NULL) {
            *tail = prev;
            prev->next = NULL;
        } else {
            b = a;
            a = prev;
            b->prev = a;
            a->next = b;
        }
    }
}


/* Takes a free particle, initialises it from the emitter and starts it on the unit sphere at the two angles;
   appends it to the burst group. Does nothing when no particle is free or its life comes out as 0. */
void EftPart10_Emit(EftPart10 *em, EftPart10Group *g, f32 yaw, f32 pitch);

/* Fills a particle from the emitter's current key values, each drawn from [value, value + range] with the VU0
   generator; coin flips use libc rand(). Returns 0 when the life comes out as 0. */
s32 EftPart10_InitPtcl(EftPart10Ptcl *p, EftPart10 *em);

/* Builds the four world-space corners of a particle that is not drawn facing the camera: a square of the
   particle's size, scaled, moved to the particle's offset, turned and placed at the emitter. */
void EftPart10_BuildCorners(EftPart10Ptcl *p, EftPart10 *em);

/* Appends a particle to a burst group. */
void EftPart10_LinkPtcl(EftPart10Ptcl **head, EftPart10Ptcl **tail, EftPart10Ptcl *p);

/* Removes a particle from a burst group. */
void EftPart10_UnlinkPtcl(EftPart10Ptcl **head, EftPart10Ptcl **tail, EftPart10Ptcl *p);


/* Queues a particle as a textured strip through its four world-space corners (projected with the loaded
   matrix; dropped when the projection clips), at the average depth of the corners. */
void EftPart10_DrawQuad(Vec4 *corner, EftXVec uv0, EftXVec uv1, EftXVec color, s32 layer, s32 texIdx, s32 noDepth,
                        EftXTexEntry *tex);

/* The same quad through the clipping polygon path: two triangles (corners 0 1 2 and 1 2 3). */
void EftPart10_DrawQuadClipped(Vec4 *corner, EftXVec uv0, EftXVec uv1, EftXVec color, s32 layer, s32 texIdx,
                               s32 noDepth, EftXTexEntry *tex);

/* Queues a particle that faces the camera through the clipping polygon path: a w x h rectangle (half sizes)
   stretched by `scale`, turned by `rot` in the view plane and placed at `pos`; two triangles at the depth slot
   of `pos` times zScale. Nothing is drawn when `pos` is behind the near plane. */
void EftPart10_DrawBillboardClipped(Vec4 *pos, f32 w, f32 h, Vec4 *color, Vec4 *scale, f32 u0, f32 v0, f32 u1,
                                    f32 v1, f32 rot, s32 layer, s32 noDepth, u64 tex0, f32 zScale);

/* Queues a particle as a screen-aligned textured quad around the projection of `pos`: w x h are half sizes and
   (offX, offY) the centre offset, all in 1/16 world units scaled by the perspective of `pos`; `rot` turns it
   about the view axis. Dropped when smaller than 2 units or when a corner leaves the GS drawing area.
   The order in which integer and float parameters are interleaved is not known (they travel in separate
   registers); this one reproduces the original's register allocation. */
void EftPart10_DrawBillboard(Vec4 *pos, Vec4 *color, f32 w, s32 offX, s32 offY, f32 h, f32 u0, f32 v0, s32 layer,
                             f32 u1, f32 v1, s32 noDepth, u64 tex0, f32 rot);

/* Draws the emitter's spin and scale: with definition flag 0x20 one random value each, otherwise three random
   keys turned into per-frame steps before and after spinMid. */
void EftPart10_InitSpin(EftPart10 *em);

/* Steps the emitter's spin, scale and burst count along their keys and turns the emitter by the spin. */
void EftPart10_UpdateSpin(EftPart10 *em);

/* Starts a segment of the emitter's key-frame animation: at age 0 the first (keys 0 to 1), once the age
   reaches keyMid the second (keys 1 to 2). Stores the change of every value over the segment. */
void EftPart10_StartKeys(EftPart10 *em);

/* Advances the key-frame animation: every value = its key at the start of the segment + change * progress. */
/* The temporary is reached through a pointer variable (`p`); with `&tmp` at every use the `seg = 0` store is
   scheduled in front of the memset call instead of behind it (presumably the pointer's own set takes that
   scheduler slot and reload deletes it afterwards: not verified). The clamp is the conditional expression. */
void EftPart10_UpdateKeys(EftPart10 *em);

/* Sets every animated value of the emitter to key `idx` of its definition. */
void EftPart10_SetKey(EftPart10 *em, s32 idx);

/* Chooses the emitter's two pack textures; the blended TEX0 goes to entry a + b of the table (b when equal). */
void EftPart10_SelectTex(EftPart10 *em, EftXTexEntry *tbl, s32 a, s32 b);

/* Builds the emitter's TEX0 (texture A with the CLUT of texture B) once per frame into its table entry. */
void EftPart10_BuildTex(EftPart10 *em, EftXTexSet *tex);

/* Creates an emitter task. Returns the task, the handle the other calls take. */
EftXTask *EftPart10_Create(EftPart10Arg *arg);

/* Lets the emitter finish: it keeps emitting for the hold time, then fades for the fade time, then stops
   emitting; the task dies when its last particle is gone. */
void EftPart10_Stop(EftXTask *task);

/* Sets the length of the fade that follows EftPart10_Stop, in frames. */
void EftPart10_SetFade(EftXTask *task, s32 frames);

/* Makes the emitter and its particles disappear at its next update. */
void EftPart10_Kill(EftXTask *task);

/* Moves the emitter; particles already flying stay where they are. */
void EftPart10_SetPos(EftXTask *task, EftXVec pos);

/* Moves the emitter and translates the corners of every live particle by the new position. */
void EftPart10_Warp(EftXTask *task, EftXVec pos);

/* Sets the emitter's axis. */
void EftPart10_SetDir(EftXTask *task, EftXVec dir);

/* Sets the emitter's size factor. */
void EftPart10_SetSize(EftXTask *task, f32 size);

/* Sets the emitter's life in seconds (0 = until stopped). No caller. */
void EftPart10_SetRate(EftXTask *task, f32 rate);

/* Changes the emitter's texture table and its two textures. No caller. */
void EftPart10_SetTex(EftXTask *task, EftXTexSet *tex, s32 a, s32 b);

/* Sets the number of frames before the emitter starts. */
void EftPart10_SetDelay(EftXTask *task, s32 frames);

/* Sets the number of frames the emitter keeps emitting after EftPart10_Stop. */
void EftPart10_SetHold(EftXTask *task, s32 frames);

/* Makes the emitter's particles ignore depth (drawn with the far depth value). */
s32 EftPart10_SetNoDepth(EftXTask *task);

/* Sets the effect kind the scene's "effects stopped / hidden" tests are asked about. */
s32 EftPart10_SetKind(EftXTask *task, s32 kind);

/* Non-zero while the handle is a live emitter of this module. */
s32 EftPart10_IsAlive(EftXTask *task);

/* Non-zero when a GS screen position is outside the drawing area (or behind the near plane). */
s32 EftPart10_IsCornerOffScreen(s32 x, s32 y, s32 z);
