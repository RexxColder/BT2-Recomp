#include "common.h"
#include "battle/eft_p.h"
#include "sys/gfx_ot.h"

/*
 * Power-up glow, first part of the module: 0x16DCA0..0x170A50 (22 functions, 21 matching; EftGlow_DrawParts is
 * left in assembly with the attempt in `#if 0`). The glow is what the fighter effect
 * layer starts with requests 4 / 5 (BtlFx_UpdatePowerUpLook); its tasks, manager and entry points are in eft_q.c
 * (EftGlow*), which calls EftGlow_BuildTables, EftGlow_Begin, EftGlow_Step, EftGlow_StepParts, EftGlow_FreeParts
 * and EftGlow_DrawParts of this file.
 *
 * VISUAL ONLY. Nothing here writes fighter, battle object or hit record state. What it reads from the fighter:
 * node positions, direction, rotation, fall speed, frame movement, height, the "action effect kind" and the
 * circle dash test (which only choose the order table layer of a quad).
 *
 * How it works (verified by the matching code unless marked):
 *   - gEftGlow owns a pool of quads (0xC0 bytes, 70 handed out lazily, then a free list) and two profile tables
 *     built once: 20 points sampled from a quadratic spline through the 13 control points of the configuration,
 *     and 20 unit directions from 20 to 115 degrees.
 *   - An emitter (the task's work, one per fighter) spawns up to 14 quads per frame while fewer than 0x41 are
 *     alive, walking the ten configured fighter nodes four quads at a time; angles around the fighter's axis come
 *     from libc rand().
 *   - A quad follows its node, is placed along the profile, is rotated about the axis and by the emitter's
 *     orientation of `frame` frames ago, leans by the fighter's frame movement, animates its width / length in
 *     two stages, fades in and out, and is drawn as a camera-facing textured strip of four vertices.
 *
 * Callees named by address: Mtx_Copy matrix copy; Mtx_RotateZ / Mtx_RotateX / Mtx_RotateY rotate about
 * Z / X / Y; Vec3_Set sets x, y, z; Vec4_Div divides a vector; Vec4_Clamp clamps each component;
 * Vu0Cur_ProjectPoint projects a point to GS screen coordinates.
 */

extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 asinf(f32 x);
extern f32 atan2f(f32 y, f32 x);

extern void Vec4_Copy(void *dst, void *src);
extern void Vec4_Set(EftPVec *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Add(EftPVec *dst, EftPVec *a, EftPVec *b);
extern void Vec4_Sub(EftPVec *dst, EftPVec *a, EftPVec *b);
extern void Vec4_Scale(EftPVec *dst, EftPVec *src, f32 scale);
extern void Vec3_Sub(EftPVec *dst, EftPVec *a, EftPVec *b);
extern void Vec3_Scale(EftPVec *dst, EftPVec *src, f32 scale);
extern void Vec3_Normalize(EftPVec *dst, EftPVec *src);
extern void Vec3_Cross(EftPVec *dst, EftPVec *a, EftPVec *b);
extern f32 Vec3_Dot(EftPVec *a, EftPVec *b);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(EftPVec *dst, void *m, EftPVec *src);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Vec3_Set(EftPVec *dst, f32 x, f32 y, f32 z);
extern void Vec4_Div(EftPVec *dst, EftPVec *src, f32 div);
extern void Vec4_Clamp(EftPVec *dst, EftPVec *src, f32 lo, f32 hi);
extern s32 Vu0Cur_ProjectPoint(EftPScr *out, EftPVec *pos); /* returns a value (unused here); `void` changes the callers' registers */

extern void BtlCharApi_GetNodePos(s32 objId, s32 node, EftPVec *out);
extern void BtlCharApi_GetDir(s32 objId, EftPVec *out);
extern void BtlCharApi_GetRot(s32 objId, EftPVec *out);
extern void BtlCharApi_GetFrameMove(s32 objId, EftPVec *out);
extern f32 BtlCharApi_GetFallSpeed(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_GetActionFxKind(s32 objId);
extern s32 BtlCharApi_IsCircleDash(s32 objId);
extern s32 BtlScene_GetStageFlag(void);
extern s32 EftAura_IsVisible(s32 objId);

/* The view being drawn: only the view matrix is read. */
typedef struct EftPView {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ Mtx44 view;
} EftPView;

extern EftPView *gBtlCamView;

/* GS XYZF2 register value. */
typedef struct EftPXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftPXyzf;

typedef struct EftPGsVtx {
    /* 0x00 */ u8 rgba[4];
    /* 0x04 */ f32 q;
    /* 0x08 */ f32 s;
    /* 0x0C */ f32 t;
    /* 0x10 */ EftPXyzf xyz;
} EftPGsVtx; /* size 0x18 */

/* Triangle strip of four vertices as queued in the order table (0x90 bytes). */
typedef struct EftPQuadPkt {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftPGsVtx v[4];
} EftPQuadPkt;

/* Links a packet into the chain of a depth slot (clamped to 0..0xFFF); layers 2 and 3 are 0 and 1. */
static inline void EftPOt_Add(OtPrim *p, s32 z, s32 layer);

/* Quadratic spline point of three control points at t, w = 1 (the same curve as EftMath_Spline3). */
void EftGlow_Spline3(EftPVec *out, EftPVec *p, f32 t);

/* The profile directions of gEftGlow seen as four floats WITHOUT the 16-byte alignment of EftPVec. The original
   forms the address of dir[i].y / .z as (gEftGlow + 4) + (i * 16 + 0x160) in front of the cosf / sinf calls:
   the compiler adds a member's offset to the base register first only when the alignment it knows for the
   element equals the alignment of the member's mode (4 for a float), so the element type was not 16-aligned
   where this was compiled. With EftPVec the offset stays in the store (`swc1 $f0,4(s0)`). */
typedef struct EftPVecU {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w;
} EftPVecU;
typedef struct EftPGlowDirView {
    /* 0x000 */ u8 pad[0x160];
    /* 0x160 */ EftPVecU dir[20];
} EftPGlowDirView;
#define GLOWDIR (((EftPGlowDirView *)gEftGlow)->dir)

/* Builds the two profile tables of gEftGlow: 20 spline samples of the scaled control points, 20 directions. */
void EftGlow_BuildTables(void);

/* Profile point idx scaled; its y is scaled again by the configuration. */
void EftGlow_GetShapePoint(EftPVec *out, s32 objId, s32 idx, f32 scale);

/* Profile direction idx with its y scaled. */
void EftGlow_GetShapeDir(EftPVec *out, s32 objId, s32 idx, f32 y);

/*
 * Orientation of the glow. Kinds other than 5: pitch from the fighter's direction (with the fall speed -1 / +1
 * added to its y for kinds 3 / 4) and yaw = the fighter's yaw + pi. Kind 5: the line from node 0x2E to node 3.
 */
void EftGlow_CalcFrame(Mtx44 *m, s32 objId, s32 kind);

/* What every quad's direction leans by this frame: a random length along node 0x30 -> node 3, plus the fighter's
   frame movement (scaled, each component clamped to +-0.5). */
void EftGlow_CalcDrift(EftPVec *out, s32 objId);

/* Flags of a new quad from the emitter's state. */
s32 EftGlow_CalcPartFlags(EftPGlow *e, s32 pair, s32 odd);

/* Target alpha of a new quad. */
f32 EftGlow_GetAlpha(EftPGlow *e, s32 flags, s32 idx);

/* Length of a quad at a stage of its size animation (0 start, 1 middle, 2 end). */
f32 EftGlow_CalcLength(EftPGlowPart *p, s32 stage);

/* Width of a quad at a stage of its size animation. */
f32 EftGlow_CalcWidth(EftPGlowPart *p, s32 stage);

/* Takes a quad from the free list, or the next unused one of the array (70 at most), and links it as active. */
EftPGlowPart *EftGlow_AllocPart(void);

/* Creates one quad at the emitter's current node. Eleven or more draws of libc rand().
   Notes for the match: in the first colour branch (flags 2) the three statements behind Vec4_Sub stand in BOTH
   arms (the compiler merges them, and with them the two `jal Vec4_Sub`, into one tail); the float parameter is
   reused as the constant 1.0 after it was stored; `inv` is 0.0 until a branch gives it the fade rate, and the
   paired branch (flags 0x20 without 2) passes the OLD value (0.0) as the x / y / z colour steps. */
EftPGlowPart *EftGlow_SpawnPart(EftPGlow *e, s32 objId, f32 angle, EftPVec *scale, s32 odd, s32 pair);

/* The emitter's colour table without the 16-byte alignment of EftPVec (see EftPVecU above): the original computes
   `e + idx * 16 + 0x260` three times, once per component read, which this compiler does only for an element
   type whose alignment equals the float's. */
typedef struct EftPGlowColorView {
    /* 0x000 */ u8 pad[0x260];
    /* 0x260 */ EftPVecU color[4];
} EftPGlowColorView;
#define GLOWCOL(e) (((EftPGlowColorView *)(e))->color)

/* Makes p the partner of a trailing quad: same profile and side, 1.5 times its life, pushed back along its
   direction, fading towards a random colour of the emitter. One draw of libc rand(). */
void EftGlow_PairPart(EftPGlow *e, EftPGlowPart *p, EftPGlowPart *src);

/* Spawns the emitter's next quad (and sometimes its partner) and advances the node walk. Angles around the
   fighter's axis depend on the node; draws of libc rand(): 1 for the angle, 0..2 for the partner, 4 when the walk
   wraps. */
void EftGlow_SpawnNext(EftPGlow *e, s32 objId);

/* Starts the emitter of a fighter (arg[0] = object id). Four draws of libc rand(). */
void EftGlow_Begin(EftPGlow *e, s32 *arg);

/* Shifts the orientation history by one frame; while not fading out, frame 0 is recomputed first. */
void EftGlow_UpdateFrames(EftPGlow *e, s32 objId);

/* Spawns up to 14 quads this frame, keeping at most 0x41 alive. */
void EftGlow_Emit(EftPGlow *e, s32 objId);

/* Per-frame emitter update: node positions, orientation history, emission, fade in / out (flag 4 when gone). */
void EftGlow_Step(EftPGlow *e, s32 objId);

/* Returns every quad of a fighter to the free list. */
void EftGlow_FreeParts(s32 objId) {
    EftPGlowPart **link = &gEftGlow->active;
    EftPGlowPart *p;

    while (*link != NULL) {
        p = *link;
        if (p->objId != objId) {
            link = &p->next;
        } else {
            *link = p->next;
            p->next = gEftGlow->free;
            gEftGlow->free = p;
        }
    }
}

/* Per-frame update of a fighter's quads: position, direction, size animation, colour fade, life. */
void EftGlow_StepParts(EftPGlow *e, s32 objId);

/* Matrix of a quad at pos whose z axis is dir bent towards (or away from) the camera's forward by 0.4 of their
   dot product, x across the view and y completing the frame. */
void EftGlow_MakeFacingMtx(Mtx44 *m, EftPVec *dir, EftPVec *pos);

/* Matched once Vu0Cur_ProjectPoint was declared with its return value (`s32`, as its definition has): with the
   local `void` prototype the three off-screen tests came out with x / the limit 0xFFF0 / the record pointer
   copies in permuted registers (9 of 487 instructions), because a call that returns nothing leaves v0 free for
   local allocation in the block behind it. Same cause as EftAura_DrawFlames (eft_n.c). */
/* Draws a fighter's quads (not the trailing ones): each is projected, skipped when a corner is off the GS
   coordinate range or behind the near plane, and queued in the order table by its average depth. */
void EftGlow_DrawParts(EftPGlow *e, s32 objId, f32 alpha);
