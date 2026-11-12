#include "common.h"
/* BT2 targets of these calls / globals (checked against the original relocations). */
#define Vec4_Add func_00312638
#define Vec4_Scale func_00312680

/* Float constants: the original .lit4 words (bits checked against the data). */
extern const f32 D_00384284; /* 0.98f */
extern const f32 D_00384288; /* 0.3f */
extern const f32 D_0038428C; /* 30.0f/31.0f */
extern const f32 D_00384290; /* 30.0f/31.0f */
extern const f32 D_00384294; /* 30.0f/31.0f */
extern const f32 D_00384298; /* 0.35f */
extern const f32 D_0038429C; /* 0.98f */
#include "battle/eft_d.h"
#include "sys/dma.h"
#include "sys/gfx.h"

/*
 * Stage-change transition: 0x13C300..0x13F430. First part (to 0x13EA00): how a particle is drawn (three
 * routines), the model drawn around the camera, the six particle initialisers and their seven per-frame updates.
 * Second part (merged in at integration from the head of eft_e.c): the task that owns them (EftBurst_Init /
 * Update / Draw / Start, 0x13EA00..0x13F3D8) and the two screen-position tests.
 *
 * One original source file, 0x13C300..0x13F430:
 * - EftBurst_Update only matches with EftBurst_InitFlash / InitRing / InitDebris defined above it;
 * - the two non-static inline functions the object emits at its end, Eft_IsScreenPosVisible (0x13F3D8) and
 *   Eft_IsScreenPosInFront (0x13F420), are the tests inlined in EftBurst_DrawModel and in the three particle
 *   draw routines (`scr[i][2] > 0`);
 * - the file's small data starts at gEftBurst (0x2FE9C8) and gEftBurstStreakAngle (0x2FE9CC), followed by the
 *   three -0.0f constants of InitFlash / InitRing / InitGlow (0x2FE9D0..0x2FE9DC), which this compiler puts in
 *   .sdata because `li.s` cannot express -0.0f.
 *
 * Nothing here touches the simulation. Everything is in camera space (the particles live around z = -50 in
 * front of the camera and are projected with the view's matrix at +0x140), so the transition looks the same
 * wherever the camera is. All randomness is libc rand(), consumed only when a particle is created.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 sqrtf(f32 x);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Tex_Upload(EftBurstTex *tex, s32 x, s32 y); /* uploads a texture entry; the two numbers are GS block pointers (tbp, cbp), not a position */
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b); /* matrix product */
extern void Mtx_Transpose(Mtx44 *dst, Mtx44 *src);
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotation about one axis */
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotation about another axis */
extern void IVec4_Set(f32 *out, s32 a, s32 b, s32 c, s32 d); /* three packed 16-bit values to a vector */
extern void IVec4_ToFloat12(f32 *out, f32 *in);
extern void IVec4_ToFloat(f32 *out, s32 *in); /* integer vector to float vector */
extern void Vec4_ToInt(s32 *dst, Vec4 *src); /* float vector to integer vector */
extern void Vec4_Clamp(f32 *out, f32 *in, f32 min, f32 max); /* clamps a vector */
extern s32 Mtx_ProjectPoint(EftScrPos *out, Mtx44 *m, Vec4 *v); /* projects one point */
extern void Mtx_ProjectPointStq(s32 *scr, f32 *st, Mtx44 *m, f32 *pos, f32 *nrm); /* projects, makes env-map st */

/* Local vectors as plain arrays (sceVu0FVECTOR / sceVu0IVECTOR style): 16-byte aligned, so the compiler
   copies them with 64-bit loads. */
typedef f32 EftFVec[4] __attribute__((aligned(16)));
typedef s32 EftIVec[4] __attribute__((aligned(16)));

/* The same as a struct, for an initialised local that is built in place. */
typedef struct EftVec16 {
    f32 v[4];
} __attribute__((aligned(16))) EftVec16;

/* The part of the camera view (gBtlCamView) the transition reads. */
typedef struct EftView {
    /* 0x000 */ u8 unk0[0x40];
    /* 0x040 */ Mtx44 unk40;    /* DrawSprite: its transform (Mtx_Transpose) is applied to the sprite's corners */
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 proj;     /* camera space to screen */
} EftView;

extern EftView *gBtlCamView;

/* Draws a particle as a camera-facing quad whose alpha rises and falls over its life. */
void EftBurst_DrawQuad(EftBurstPtcl *p);

/* Draws a particle as a quad that can be scaled per axis, rotated by its angles and tinted. The tables are
   D_002EC800 (corners) and D_002EC840 (st) in .rodata. `ps` (as in EftBurst_DrawQuad) is needed only for the
   Mtx_ProjectPoint call: with scr[i] there, the copy of the two tables uses other temporaries. */
void EftBurst_DrawQuadRot(EftBurstPtcl *p);

/* Draws a particle as an axis-aligned sprite; its two corners are turned by the view's matrix at +0x40. */
void EftBurst_DrawSprite(EftBurstPtcl *p);

/* Turns the offsets inside the burst model file into pointers (once). */
void EftBurst_RelocateModel(EftBurstModel *model);

/* GS state for the model: TEX1, TEST, ZBUF, ALPHA, COLCLAMP and FRAME (colour only) for both contexts. */
u64 *EftBurst_PutModelEnv(u64 *p);

/* GS state after the model: TEX1, TEST (always pass), ZBUF, COLCLAMP, FRAME with every channel writable. */
u64 *EftBurst_PutModelEnvEnd(u64 *p);

/* Fills the alpha plane of the frame buffer with 0x80 (one full-screen sprite through context 2). */
void EftBurst_ClearAlphaPlane(void);

#if 0 /* ATTEMPT: not matching: 597 instructions against 599, 44 differ in an aligned listing, all of them register
   choice and instruction order in three places of the vertex loop; the control flow, the frame (0x240), every stack
   slot, every call and every packet word are the original's. What differs:
   - the colour unpack: the original reads rgba[0] and rgba[2] into $v1 and the two high bytes into $v0, and
     takes the three low parts of the first RGBAQ word from those registers (`move a1,v1`, `move a2,v0 /
     dsll a2,a2,8`, `move a0,v1 / dsll a0,a0,16`), reloading only rgba[3] from the stack; here the registers
     alternate the other way round and rgba[2] is reloaded too (2 instructions short). The moves are sign
     extending loads of rgba[i] that the post-reload CSE turned into copies, so the first scheduling pass of the
     original must have put the reads of rgba[0] and rgba[1] behind the store of rgba[1] and in front of the load
     of the third byte, not into the load-delay gaps where they land here. Reading / storing through a pointer
     that the compiler cannot resolve (`c = rgba;` set outside the vertex loop) gives the original's register
     pattern but costs two instructions elsewhere; a `do { } while (0)` around the four stores does too but breaks
     the loop's induction pointers.
   - the copies of the two constant vectors: the original loads the address of D_002EC8D0 into $v1 and copies it
     to $t0 for the second half (`move t0,v1 ... ld v0,0(v1) / ld v1,8(t0)`), with the halves in $a3/$a2 and
     $v0/$v1; here both addresses go through $t0 and the halves sit in $a2/$a3 and $v1/$v0.
   - the last two argument moves in front of Mtx_ProjectPointStq are swapped (`move t0,s0 / move a3,v0`).
   Ruled out (about 250 variants): every element type / alignment for the vectors, `static const` tables copied by
   struct assignment, memcpy, u64 pairs (u128 gives lq / sq and is the only form that keeps the lui / addiu in the
   block), colour bytes as u8, bit fields, temporaries, one u32, casts, statement permutations, the position of
   `env`, `pos[3]`, `vis`.
   What the rewrite established (and the previous attempt had wrong in shape, not in behaviour):
   - a triangle record is a structure, { s16 vtx[3]; s16 nrm[3][2]; u16 col[3][2]; }: the colour is read as two
     16-bit words split with `& 0xFF` and `>> 8` (lbu / lhu + srl), and the multiple-of-16 split of the member
     offsets gives the original's two extra walking pointers (tri + 2, tri + 6);
   - `((x >> 8) & 0xFF)` with the redundant mask is required: without it the vertex loop is one instruction
     shorter for the loop pass and `tri->vtx[k]` becomes a walking pointer as well (the test is
     `lifetime * threshold * benefit < insn_count`, here 264 against 264);
   - the packing casts are (u64), not (s64): this compiler reassociates `a | b << 8 | c << 16 | d << 24 | q << 32`
     differently for the two ((a | q) | (c << 16 | b << 8)) | d << 24 is the (u64) form);
   - TEX0_2 is `tex0 | (y << 37 | x | 0x400000000)` with the parentheses;
   - the group loop is `for (i = 0; i < n; i++)` (reversed by the compiler into the counter at sp+0x18C), not a
     loop on n itself; the triangles are written out without a loop, two words at a time;
   - the visibility test is the inline function Eft_IsScreenPosVisible used as a value (`vis += ...`);
   - the light vectors are block-scope initialised arrays ({0, 0, 0, 1} is "mostly zero", so it becomes
     memset + one store). */
typedef struct EftBurstTri {
    /* 0x00 */ s16 vtx[3];
    /* 0x06 */ s16 nrm[3][2];   /* two packed angles per corner (env-map normal) */
    /* 0x12 */ u16 col[3][2];   /* r | g << 8, b | a << 8 */
} EftBurstTri; /* 0x1E */

/* Eft_IsScreenPosVisible (0x13F3D8, emitted at the end of the object) as the compiler inlined it here. */
static inline s32 EftBurst_IsVisible(s32 *pos);

/* Draws the burst's model in camera space: every vertex is three 16-bit angles / a radius turned into a
   point around (0, 0, -50), every triangle is sent as RGBAQ / ST / XYZ2. Groups with flag 0x800 get a
   second, environment-mapped pass through GS context 2 whose colour is a light that fades with the
   distance to the centre and grows with the frame counter. */
void EftBurst_DrawModel(EftBurstModel *model, s32 unused);
#endif


/* Uploads a texture unless it is already the current one. */
void EftBurst_SetTexture(EftBurstTex *tex, s32 x, s32 y);

/* Returns the first free particle, NULL when all 350 are in use. */
EftBurstPtcl *EftBurst_AllocPtcl(void);

/* Spark: starts on the burst's axis and flies towards the camera in a narrow cone. */
void EftBurst_InitSpark(EftBurstPtcl *p, s32 idx);

/* Streak: a rotated quad on a circle around the axis, pulled back towards it; re-created when it ends. */
void EftBurst_InitStreak(EftBurstPtcl *p);

/* Flash: a quad on the axis that grows by 20% a frame for ten frames. */
void EftBurst_InitFlash(EftBurstPtcl *p);

/* Ring: a quad that swells and shrinks over eight frames. */
void EftBurst_InitRing(EftBurstPtcl *p);

/* Glow: a quad on the axis that grows slowly for 47..62 frames. */
void EftBurst_InitGlow(EftBurstPtcl *p);

/* Debris: a sprite scattered around the axis, drifting away from it. */
void EftBurst_InitDebris(EftBurstPtcl *p);

/* Flash: moves, slows down, grows; ends when its life runs out. */
s32 EftBurst_UpdateFlash(EftBurstPtcl *p);

/* Streak: spirals in towards the axis while its angles advance; starts over when its life ends. */
s32 EftBurst_UpdateStreak(EftBurstPtcl *p);

/* Spark: moves, slows down, shrinks, fades over its last ten frames. */
s32 EftBurst_UpdateSpark(EftBurstPtcl *p) {
    Vec4_Add(&p->pos, &p->pos, &p->vel);
    Vec4_Scale(&p->vel, &p->vel, D_00384284);
    p->scale -= D_00384288;
    if (p->life < 10) {
        p->alpha = p->life;
    }
    if (p->flags & EFT_BURST_F_TIMED) {
        if (p->life != 0) {
            p->life--;
        } else {
            return 0;
        }
    }
    return 1;
}

/* Moves and slows down; ends when its life runs out. Not referenced. */
s32 EftBurst_UpdateMove(EftBurstPtcl *p) {
    Vec4_Add(&p->pos, &p->pos, &p->vel);
    Vec4_Scale(&p->vel, &p->vel, D_0038428C);
    if (p->flags & EFT_BURST_F_TIMED) {
        if (p->life != 0) {
            p->life--;
        } else {
            return 0;
        }
    }
    return 1;
}

/* Ring: scale rises to size / 2 + 10 at half life and falls back. */
s32 EftBurst_UpdateRing(EftBurstPtcl *p) {
    Vec4_Add(&p->pos, &p->pos, &p->vel);
    Vec4_Scale(&p->vel, &p->vel, D_00384290);
    p->scale = (f32)(p->lifeMax - p->life) / (f32)p->lifeMax;
    if (p->scale > 0.5f) {
        p->scale = 1.0f - p->scale;
    }
    p->scale = p->scale * p->size + 10.0f;
    if (p->flags & EFT_BURST_F_TIMED) {
        if (p->life != 0) {
            p->life--;
        } else {
            return 0;
        }
    }
    return 1;
}

/* Glow: moves, slows down, grows by 0.35 a frame. */
s32 EftBurst_UpdateGlow(EftBurstPtcl *p) {
    Vec4_Add(&p->pos, &p->pos, &p->vel);
    Vec4_Scale(&p->vel, &p->vel, D_00384294);
    p->scale += D_00384298;
    if (p->flags & EFT_BURST_F_TIMED) {
        if (p->life != 0) {
            p->life--;
        } else {
            return 0;
        }
    }
    return 1;
}

/* Debris: moves, slows down; alpha is a triangle wave over its life (peak 24). */
s32 EftBurst_UpdateDebris(EftBurstPtcl *p) {
    Vec4_Add(&p->pos, &p->pos, &p->vel);
    Vec4_Scale(&p->vel, &p->vel, D_0038429C);
    p->alpha = p->life * 48 / p->lifeMax;
    if (p->alpha >= 25) {
        p->alpha = 48 - p->alpha;
    }
    if (p->flags & EFT_BURST_F_TIMED) {
        if (p->life != 0) {
            p->life--;
        } else {
            return 0;
        }
    }
    return 1;
}

/* ------------------------------------------------------------------------------------------------------------
 * Second part (formerly the head of eft_e.c, 0x13EA00..0x13F430), with its own header and view types. Names the first part already declared with
 * other types are reached through cast macros (the generated code is the same).
 * ------------------------------------------------------------------------------------------------------------ */
/* eft_e.h declares the transition's globals and the view with its own types: hide those declarations and reach
 * the globals through casts. */
#define EftView EftViewE
#define gEftBurstRes gEftBurstRes_eDecl
#define gEftBurst gEftBurst_eDecl
#include "battle/eft_e.h"
#undef gEftBurstRes
#undef gEftBurst
#define gEftBurstRes (*(EftTransRes *)&gEftBurstRes)
#define gEftBurst ((EftTransWork *)gEftBurst)
#include "sys/gfx_ot.h"

/*
 * Effect code 0x13EA00..0x13F430 (the declarations below are the common preamble of the former eft_e.c, whose
 * rest, 0x13F430..0x142CA0, is still eft_e.c). See include/battle/eft_e.h for the layouts.
 *
 *   0x13EA00..0x13F3D8  EftBurst_*: the stage-change transition (task side; particles and model are above).
 *   0x13F3D8..0x13F430  two screen-position tests, no callers.
 *
 * Other modules are declared locally with this file's own view types (the integrator was linking while this was
 * written). Names of the task system (BtlTask*), EftCam_*, EftStage_*, EftHit_*, EftUtil_*, EftRec_*, BtlStage_*
 * and the EftWater* pool functions are the ones recorded in config/symbols by their owners.
 *
 * Random numbers: everything here draws from the C library rand() (EFT_RANDF) except EftSteam_Emit, which uses
 * the VU0 generator through Rand_FloatRange. No draw reaches a fighter, a hit record or a battle object.
 */

extern void *Heap_Alloc(s32 size, u32 align, s32 fromTail, s32 heap);
extern void Heap_Free(void *ptr);
extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern void *BtlTask_CreateChildList(void *task, s32 capacity, s32 workSize);
extern void *BtlTaskList_AddTail(void *list, BtlTaskClass *cls, void *arg);
extern void BtlTask_SetDead(void *task);
extern void EftCam_Start(s32 *arg);
extern void EftCam_SetHold(s32 arg);
extern void EftCam_Stop(void);
extern void Gfx_AddDefaultEnv(void);
#define EftBurst_DrawModel ((void (*)(void *model, s32 arg))EftBurst_DrawModel)
#define EftBurst_SetTexture ((void (*)(void *tex, s32 x, s32 y))EftBurst_SetTexture)
#define EftBurst_RelocateModel ((void (*)(void *model))EftBurst_RelocateModel)
extern void Res_RelocateOffsets(void *dst, void *base, void *table);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);

extern s32 BtlStage_GetFxResC(void);
extern s32 BtlStage_GetFxResA(void);
extern EftStageMarker *BtlStage_GetFxResC2(void);
extern void EftTexSet_Load8(EftSteamTex *tex, s32 *data);
extern u64 EftVram_AddTex(u64 *tex0, s32 a1, s32 a2);
extern s32 EftStage_IsDrawOn(void);
extern void Vu0Cur_Push(void);
extern void Vu0Cur_LoadMtx(Mtx44 *mtx);
extern void Vu0Cur_Pop(void);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Rand_FloatRange(f32 a, f32 b);

/* The stage state (gp 0x2FEBE0); only the flag word. */
typedef struct EftStageState {
    s32 unk0[2];
    s32 flags; /* bit 0: not drawable (BtlStage_IsReady tests it too) */
} EftStageState;
extern EftStageState *gBtlStage;

/* The view being drawn (btl_cam.h); only the matrices and position used here. */
typedef struct EftView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
    /* 0x180 */ u8 unk180[0xA0];
    /* 0x220 */ Vec4 pos;
} EftView;
#define gBtlCamView ((EftView *)gBtlCamView)

extern f32 sqrtf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern s32 BtlStage_GetWaterLevel(f32 *y);
extern s32 BtlStage_GetId(void);
extern s32 Battle_IsSplitScreen(void);
extern s32 BtlStage_IsReady(void);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern f32 BtlCharApi_GetGroundY(s32 objId);
extern void BtlCharApi_GetPos(s32 objId, Vec4 *out);
extern void BtlCharApi_GetDir(s32 objId, Vec4 *out);
extern f32 BtlCharApi_GetSpeed(s32 objId);
extern s32 BtlCharApi_IsInTechnique(s32 objId);
extern void BtlCharApi_PlaySoundAt(Vec4 *pos, s32 kind, s32 id, f32 near, f32 far);
extern f32 EftHit_GetRadiusA(EftWaterBlast *rec);
extern void EftUtil_ClipSegToWater(EftEVec *out, Vec4 *a, Vec4 *b);
extern s32 EftRec_GetDefClass(EftWaterBlast *rec);
extern void EftTexSet_Load32(u8 *tex, s32 *data);
extern void EftWater_UpdateTextures(s32 a0, s32 a1);
extern void EftWaterSplash_UpdateList(EftWaterSplash **head, EftWaterSplash **tail);
extern void EftWaterSplash_DrawList(void *head);
extern void EftWaterTrail_Spawn(void **head, void **tail, s32 objId, EftWaterBlast *rec);
extern void EftWaterTrail_UpdateList(void **head, void **tail);
extern void EftWaterTrail_DrawList(void *head);
extern void EftWaterDrop_UpdateList(void **head, void **tail);
extern void EftWaterDrop_DrawList(void *head, EftEVec origin);
extern void EftWaterRing_UpdateList(void **head, void **tail);
extern void EftWaterRing_DrawList(void *head);
extern void EftWaterSpray_UpdateList(void **head, void **tail);
extern void EftWaterSpray_DrawList(void *head, EftEVec origin);
extern void EftWaterMist_UpdateList(void **head, void **tail);
extern void EftWaterMist_DrawList(void *head);

/* Billboard: yaw / pitch / speed of its flight, rot, size and its growth, gravity, life, start delay. */
extern void EftWaterDrop_Spawn(void **head, void **tail, EftEVec pos, f32 yaw, f32 pitch, f32 speed, f32 rot, f32 rotVel,
                          f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity, f32 life, f32 delay, u8 r, u8 g, u8 b,
                          u8 tex, u8 layer, s32 flags);
/* Ring lying on the surface. */
extern void EftWaterRing_Spawn(void **head, void **tail, EftEVec pos, f32 rot, f32 size, f32 sizeVel, f32 sizeDamp,
                          f32 alphaMax, f32 time, f32 delay, u8 r, u8 g, u8 b, u8 tex, u8 layer, s32 flags);
/* Streak thrown out along a direction. */
extern void EftWaterSpray_Spawn(void **head, void **tail, EftEVec pos, f32 dist, f32 height, f32 yaw, f32 pitch, f32 roll,
                          f32 tilt, f32 tiltEnd, f32 speed, f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity,
                          f32 nearScale, f32 widthScale, f32 life, f32 delay, u8 r, u8 g, u8 b, u8 tex, u8 layer,
                          s32 flags);
/* Streak that orbits. */
extern void EftWaterMist_Spawn(void **head, void **tail, EftEVec pos, f32 radius, f32 height, f32 yaw, f32 yawVel,
                          f32 yawDamp, f32 pitch, f32 roll, f32 tilt, f32 tiltEnd, f32 speed, f32 size, f32 sizeVel,
                          f32 sizeDamp, f32 gravity, f32 nearScale, f32 widthScale, f32 life, f32 delay, u8 r, u8 g,
                          u8 b, u8 tex, u8 layer);

#define EFT_RANDF() ((f32)rand() / 2147483647.0f)
#define EFT_UNIT(objId) (BtlCharApi_GetHeight(objId) * 0.05f)
#define EFT_SCALE(objId, scale) (BtlCharApi_GetHeight(objId) * 0.05f * (scale))
#define EFT_PAUSED() (Battle_GetWork()->flags & 0x100)

/* The battle work (battle.h); only the flag word. */
typedef struct EftBattleWork {
    u8 unk0[0x19F0];
    u64 flags; /* 0x100: pause */
} EftBattleWork;
extern EftBattleWork *Battle_GetWork(void);

extern EftEVec D_002C3630; /* (0, 0, 0, 1) */

#define EftBurst_AllocPtcl ((EftTransPart *(*)(void))EftBurst_AllocPtcl)
#define EftBurst_InitSpark ((void (*)(EftTransPart *part, s32 idx))EftBurst_InitSpark)
#define EftBurst_InitStreak ((void (*)(EftTransPart *part))EftBurst_InitStreak)
#define EftBurst_InitFlash ((void (*)(EftTransPart *part))EftBurst_InitFlash)
#define EftBurst_InitRing ((void (*)(EftTransPart *part))EftBurst_InitRing)
#define EftBurst_InitGlow ((void (*)(EftTransPart *part))EftBurst_InitGlow)
#define EftBurst_InitDebris ((void (*)(EftTransPart *part))EftBurst_InitDebris)
extern s32 Snd_PlaySeEx(u32 mask, s32 id, s32 volume, s32 pan, s32 pitch);

extern f32 EftStage_GetTintScale(void);
extern void EftMath_MtxFromDir(Mtx44 *out, Vec4 *dir, f32 angle);
extern void Mtx_MulVec4(Vec4 *out, Mtx44 *mtx, Vec4 *v);

/* A projected point as Vu0Cur_ProjectPoints writes it: GS x, y in 12.4 fixed point, z, and a fourth word. */
typedef struct EftSteamScr {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s32 unkC;
} EftSteamScr; /* size 0x10 */
extern void Vu0Cur_ProjectPoints(EftSteamScr *out, Vec4 *in, s32 count);

/* GS XYZF2 register value. */
typedef struct EftSteamXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftSteamXyzf;

/* The packet of one particle quad: REGLIST of PRIM, TEX0_1, RGBAQ and four (ST, XYZF2). */
typedef struct EftSteamPkt {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u8 rgba[4];
    /* 0x34 */ f32 q;
    /* 0x38 */ struct {
        /* 0x00 */ f32 s;
        /* 0x04 */ f32 t;
        /* 0x08 */ EftSteamXyzf xyz;
    } v[4];
    /* 0x78 */ u64 pad;
} EftSteamPkt; /* size 0x80 */


typedef struct EftCommonRes {
    u8 unk0[0x34];
    s32 *transition;
} EftCommonRes;
extern EftCommonRes *gCommonRes;

/* Layer 4 init: creates the list that will hold the one transition task. */
void EftBurstLayer_Init(void *task);

/* Layer 4 term: nothing. */
void EftBurstLayer_Term(void);

/* Layer 4 update: creates the transition task once EftBurst_Start has asked for it. */
void EftBurstLayer_Update(void);

/* Transition task init: allocates the work, clears the particles and starts the camera animation. */
void EftBurst_Init(void);

/* Transition task term: frees the work. */
void EftBurst_Term(void);

/* Transition task update. On the frame EftBurst_End was called: ends the task and stops the camera animation.
   Otherwise, unless the battle is paused: spawns particles on a fixed schedule (frame 0 two rings, 7 and 30 a
   flash, 10 a burst of 240 streaks, 32 sparks and 16 debris, from 9 a glow every 5..8 frames, from 11 one spark
   and one debris per frame), counts the frame to 151, widens the fade distance, advances the sway (rand()), runs
   every particle, and plays the sounds (4 / 0x4A at frames 7 and 30 and then every 60..139 frames (rand()),
   4 / 0x47 with a 20 % chance (rand()) every 60th frame).
   Matches since the integration, for two reasons that were outside the former eft_e.c:
   - it needs EftBurst_InitFlash, EftBurst_InitRing and EftBurst_InitDebris defined earlier in the same file
     (four `beqz` come out as `beqzl` otherwise), hence the merge into this file;
   - the prelude used to leave a hazard nop after `mfhi / mtc1` (five places: the `% 360` terms); __gp_forget
     now uses `.set mips64` instead of `.set mips4`, which removes them and changes no other linked object. */
void EftBurst_Update(void *task);

/* Transition task draw: the model, then every particle that was visible in the last update. */
void EftBurst_Draw(void);

/* Transition task post-update: nothing. */
void EftBurst_PostUpdate(void);

/* Transition task reset (battle restart): stops the camera animation and ends the task. */
void EftBurst_Reset(void *task);

/* Called by the stage swap once the transition file is loaded: resolves its entries and asks for the task. */
void EftBurst_Start(void);

/* 1 while the transition is in its first 150 frames (the stage swap waits for 0 before fading out). */
s32 EftBurst_IsBusy(void);

/* Asks the transition task to end (the stage swap calls it once the fade has covered the screen). */
void EftBurst_End(void);

/* 1 when a projected point (GS 12.4 coordinates) is in front of the camera and inside the guard area. */
s32 Eft_IsScreenPosVisible(s32 *pos);

/* 1 when a projected point is in front of the camera. */
s32 Eft_IsScreenPosInFront(s32 *pos);
