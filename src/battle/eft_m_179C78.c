#include "common.h"
#include "battle/eft_m.h"

/*
 * Effect tasks, 0x15F728..0x1637A0. See include/battle/eft_m.h.
 */

#define RAND_MAX_F 2147483647.0f
#define RANDF() ((f32)rand() / RAND_MAX_F)

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

/* Spawns `count` streaks in a ring around a model node of the fighter, pointing against `dir`. */
s32 EftSpdLine_SpawnStreakRing(s32 objId, Vec4 *dir, s32 node, s32 count, f32 unused, f32 lifeMin, f32 lifeRange);

/* Allocates the work once and loads the textures (common entry 0x237). */
void EftSpdLine_Init(void);

/* Frees the work. */
void EftSpdLine_Term(void);

/* Task update: steps both lists, then the texture. */
void EftSpdLine_Update(void);

/* Empty task slot. */
void EftSpdLine_Stub(void);

/* Task draw: both lists under the current view's world-to-screen matrix. */
void EftSpdLine_Draw(void);

/* Returns a zeroed free trail slot, or NULL when all 30 are in use. */
EftSpdTrail *EftSpdLine_AllocTrail(void);

/* Adds a trail at the list tail: random width scaled by the fighter's height, alpha 64, two frames of life. */
void EftSpdLine_AddTrail(s32 objId, EftVec pos, EftVec dir);

/* Steps every trail (not while paused) and unlinks the finished ones. */
void EftSpdLine_UpdateTrails(void);

/* Moves a trail with its fighter; returns 1 when its life ran out. */
s32 EftSpdLine_StepTrail(EftSpdTrail *p);

/* Draws every live trail, white with its alpha. */
void EftSpdLine_DrawTrails(void);

/* Returns a zeroed free streak slot, or NULL when all 40 are in use. */
EftSpdStreak *EftSpdLine_AllocStreak(void);

/* Adds a streak at the list tail: alpha 160, fading to 0 in `life` seconds. */
void EftSpdLine_AddStreak(s32 objId, EftVec pos, EftVec tail, EftVec dir, f32 speed, f32 life, f32 width);

/* Steps every streak (not while paused) and unlinks the finished ones. */
void EftSpdLine_UpdateStreaks(void);

/* Moves a streak along its direction and fades it; returns 1 when it is fully transparent. */
s32 EftSpdLine_StepStreak(EftSpdStreak *p);

/* Draws every live streak, black with its alpha, once the texture is ready. */
void EftSpdLine_DrawStreaks(void);

/* Corners of a trail: both ends widened across the line of sight from the camera. */
void EftSpdLine_BuildTrailQuad(Vec4 *out, EftSpdTrail *p);

/* Corners of a streak: as for a trail, with half the width on each side. */
void EftSpdLine_BuildStreakQuad(Vec4 *out, EftSpdStreak *p);

/* Sends the four corners as two triangles with one colour; the matrix argument is not used. */
void EftSpdLine_DrawQuad(Vec4 *quad, Mtx44 *mtx, EftSpdTex *tex, f32 r, f32 g, f32 b, f32 a, u8 blend, s32 inView);

/* Keeps the textures referenced while any segment is alive. */
void EftSpdLine_UpdateTexture(s32 a, s32 b);

/* ---- aura particles ------------------------------------------------------------------------------------- */

extern void EftSpr_DrawRot(u8 r, u8 g, u8 b, u8 a, f32 x, f32 y, f32 z, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot,
                          s32 t0, s32 t1, s32 w, s32 h, s32 s0, u32 size, s32 s2, s32 s3, void *tex);

/* Drift direction of a spark: against the fighter's velocity, with a random vertical part. */
void EftAura_GetSparkDir(Vec4 *out, s32 objId);

/* The same for the alternate aura: straight up / down while the action effect kind is 3 / 4. */
void EftAura_GetSparkDirAlt(Vec4 *out, s32 objId);

/* Flame direction term: away from the aura centre, plus a random left / right push across the facing. */
void EftAura_GetFlameSideDir(EftAura *aura, Vec4 *out, s32 objId, f32 power, f32 away, f32 side);

/* Flame direction term: against the motion of the body part relative to the fighter's root. */
void EftAura_GetFlameDragDir(EftAura *aura, Vec4 *pos, Vec4 *out, s32 objId, s32 part);

/* Flame direction term: outward from a random point between the aura axis and the root, scaled down by speed. */
void EftAura_GetFlameOutDir(EftAura *aura, Vec4 *out, s32 objId, s32 part, f32 power, f32 amount);

/* Bends a flame's direction: early towards its start direction and turn axis, late towards `pos`. */
void EftAura_TurnFlame(EftAuraFlame *f, Vec4 *pos, f32 t);

/* Accelerates a flame early in its life and damps it later. */
void EftAura_AccelFlame(EftAuraFlame *f, f32 t);

/* Offset from the aura axis (at the root's height) towards a body part. */
void EftAura_GetPartOffset(EftAura *aura, Vec4 *out, s32 objId, s32 part, f32 radial, f32 vertical);

/* Takes a spark from the free list, else the next unused slot; links it on the used list. */
EftAuraSpark *EftAura_AllocSpark(void);

/* Returns every spark of a fighter to the free list. */
void EftAura_FreeSparks(s32 objId);

/* Creates one spark of an emitter: random life and colour, direction from the fighter's motion. */
s32 EftAura_SpawnSpark(EftAura *aura, s32 objId, s32 emitter, s32 kind, Vec4 *offset, f32 follow);

/* Spawns the sparks of one emitter: one per `sparkStep` of the distance to its node (one only with `once`). */
void EftAura_SpawnSparks(EftAura *aura, s32 objId, s32 emitter, s32 once);

/* Moves, spins and fades a fighter's sparks; a spark at the end of its life is replaced by a new one. */
void EftAura_StepSparks(EftAura *aura, s32 objId);

/* Task entry: on the first call spawns the sparks of all twelve emitters, then steps them. */
void EftAura_UpdateSparks(EftAura *aura, s32 objId, s32 *state);

/* Draws a fighter's sparks as rotated sprites. */
void EftAura_DrawSparks(EftAura *aura, s32 objId, f32 alpha);

/* Takes a flame from the free list, else the next unused slot; links it on the used list. */
EftAuraFlame *EftAura_AllocFlame(void) {
    EftAuraFlame *p;

    if (gEftAuraPool->flameFree != NULL) {
        p = gEftAuraPool->flameFree;
        gEftAuraPool->flameFree = p->next;
    } else if (gEftAuraPool->flameNext <= gEftAuraPool->flameMax - 1) {
        p = &gEftAuraPool->flames[gEftAuraPool->flameNext++];
    } else {
        return NULL;
    }
    p->next = gEftAuraPool->flameUsed;
    gEftAuraPool->flameUsed = p;
    p->flags = 0;
    return p;
}

/* Flag word of a new flame from the aura's state. */
s32 EftAura_GetFlameFlags(EftAura *aura, s32 objId, s32 second, s32 alt);

/* Life of a new flame in frames. */
f32 EftAura_GetFlameLife(s32 flags, f32 burst);

/* Speed of a new flame. */
f32 EftAura_GetFlameSpeed(s32 flags, s32 objId, f32 level, f32 burst);

/* Peak alpha of a new flame. */
f32 EftAura_GetFlameAlpha(EftAura *aura, s32 flags, f32 alpha);

/* Stretch of a flame at a phase (0 start, 1 grown, 2 late, 3 end); 0 for an invisible flame. */
f32 EftAura_GetFlameStretch(EftAuraFlame *f, s32 objId, s32 phase);

/* Size of a flame at a phase; 0 for an invisible flame. */
f32 EftAura_GetFlameSize(EftAuraFlame *f, s32 objId, s32 phase);

/* End ratio of a flame: random, lower at speed, at least 0.65 (0.9 for the alternate kind). */
f32 EftAura_GetFlameEnd(EftAuraFlame *f, s32 objId);

/* Creates one flame at a body part. `second` makes the extra flame of kind 2 (flag 0x800). */
s32 EftAura_SpawnFlame(EftAura *aura, s32 objId, s32 part, Vec4 *pos, Vec4 *offset, f32 follow, s32 alt, s32 second);

/* Spawns the flames of one body part: one per `flameStep` of its length (one only with `once`), each with a
   possible second flame while fewer than 45 are alive. Returns the last primary spawn's result. */
s32 EftAura_SpawnFlames(EftAura *aura, s32 objId, s32 part, s32 once);

/* Marks the aura active, picks the variant from the argument, and with `reset` restarts its fade-in. */
void EftAura_Start(EftAura *aura, s32 *arg, s32 reset);

/* Returns every flame of a fighter to the free list. */
void EftAura_FreeFlames(s32 objId);

/* Moves, grows, colours and fades a fighter's flames; a flame near its end spawns its successor, a finished
   one is freed. */
void EftAura_StepFlames(EftAura *aura, s32 objId);

/* Per-frame aura state: first flames of the ten body parts, the burst and the three fades, then the flames. */
void EftAura_UpdateState(EftAura *aura, s32 objId);

/* Matrix for a flame quad: third axis along `dir` leaned by the camera's view axis, translation `pos`. */
void EftAura_BuildFlameMtx(Mtx44 *out, Vec4 *dir, Vec4 *pos);
