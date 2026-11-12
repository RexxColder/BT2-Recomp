#define gEftCam D_00387830  /* fix_targets */ /* the original uses 0x387830 here */
#include "common.h"
#include "battle/battle.h"
#include "battle/btl_pool.h"
#include "battle/eft_a.h"
#include "sys/gfx_ot.h"

/*
 * Effect core, 0x12DD80..0x132290. The object model is described in include/battle/eft_a.h.
 *
 * Callees outside this file are declared here with local views (an integrator is linking other files).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);

extern s32 BtlScene_IsTimeStopped(void);

extern void Vec4_Copy(EftVec *dst, EftVec *src);
extern void Vec4_Sub(EftVec *dst, EftVec *a, EftVec *b);
extern f32 Vec3_Dot(EftVec *a, EftVec *b);
extern void Vec3_Normalize(EftVec *dst, EftVec *src);
extern void Vec4_Set(EftVec *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Add(EftVec *dst, EftVec *a, EftVec *b);
extern void Vec4_Scale(EftVec *dst, EftVec *src, f32 scale);
extern void Vec3_Add(EftVec *dst, EftVec *a, EftVec *b);
extern void Vec3_Scale(EftVec *dst, EftVec *src, f32 scale);
extern void Vec3_Cross(EftVec *dst, EftVec *a, EftVec *b);
extern void Mtx_MulVec4(EftVec *dst, EftMtx *m, EftVec *src);
extern void Mtx_StoreIdentity(EftMtx *m);
extern void Mtx_InverseRT(EftMtx *dst, EftMtx *src);            /* inverse of a rigid transform (view -> world) */
extern void Mtx_RotateZ(EftMtx *dst, EftMtx *src, f32 angle); /* rotation about Z */
extern void Mtx_Mul(EftMtx *dst, EftMtx *a, EftMtx *b);   /* matrix product */
extern void Vec4_Div(EftVec *dst, EftVec *src, f32 div);   /* dst = src / div */
extern void Vec4_Lerp(EftVec *dst, EftVec *a, EftVec *b, f32 t); /* dst = a * t + b * (1 - t) */
extern s32 ClipPoly_ClipPlane(EftGfxVert *verts, EftVec *plane, s32 count); /* clips a polygon against a plane, new count */
extern void ClipPoly_ProjectCur(s32 (*scr)[4], EftVec *col, EftGfxVert *verts, s32 count); /* projects a polygon */
extern void EftPrim_DrawTriangle(s32 *p0, s32 *p1, s32 *p2, EftVec *uv0, EftVec *uv1, EftVec *uv2,
                          EftVec *col0, EftVec *col1, EftVec *col2, s32 arg9, s32 arg10, s32 arg11, s32 z, u64 tex);
extern s32 abs(s32 x);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atanf(f32 x);
extern f32 acosf(f32 x);
extern s32 BtlCharApi_IsLockedOn(s32 objId);
extern void BtlCharApi_CalcAimDir45(s32 objId, s32 arg, EftVec *out);
extern void BtlCharApi_GetRot(s32 objId, EftVec *out);
extern void BtlCharApi_GetFrameMove(s32 objId, EftVec *out);
extern u8 *gBtlCamView;
extern EftVec gEftClipPlanes[5];

/* Argument block of the impact effect 0x187BE0. */
typedef struct EftImpactArg {
    /* 0x00 */ EftVec pos;
    /* 0x10 */ EftVec dir;
    /* 0x20 */ s32 id;
    /* 0x24 */ s32 objId;
    /* 0x28 */ s32 unk28;
} EftImpactArg; /* size 0x30 */

extern void BtlTask_SetTagBits(EftHitTask *task, s32 bits);       /* task->flags |= bits */
extern void BtlTask_SetPos(EftHitTask *task, EftVec pos);     /* task->pos = pos */
extern void EftTechEvt_RequestStop(s32 side);                         /* beam struggle: sets bit 2 in a per-side word */
extern void EftKiBomb_SetContact(EftHitTask *task, void *mtx);    /* copies a 0x40-byte block into the blast task's work */
extern f32 BtlStage_GetInnerRadius(void);                              /* stage radius - 100 */
extern s32 EftImpact_SpawnBlast(EftImpactArg arg, f32 scale, f32 unk); /* adds an impact effect task (class 0x2C3F20) */
extern void EftGndDust_SpawnImpact(s32 objId, EftVec *pos, f32 scale);
extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, EftVec *out);
extern s32 BtlCharApi_TestFlagA4(s32 objId);
extern s32 BtlStage_HasFeature(s32 kind);                          /* stage query (0..13) */
extern void *BtlObj_Get(s32 objId);
extern f32 BtlCharApi_GetChargedUnkC78(s32 objId);
extern s32 BtlCharApi_IsInTechnique(s32 objId);
extern void DemoCam_SetAnim(void *anim);
extern void DemoCam_SetChr(void *chr);
extern void DemoCam_SetTime(f32 time);
extern f32 DemoCam_GetTime(void);
extern f32 DemoCam_GetLength(void);
extern void DemoCam_Start(void);
extern void DemoCam_Stop(void);

/* Allocates and clears the record list, then the shape arena. */
void EftHit_Init(void);

/* Frees the shape arena and the record list. */
void EftHit_Term(void);

/* Returns the free slot of the list, zeroed, for the caller to fill before EftHit_Add. */
EftHitRec *EftHit_GetNew(void);

/* Completes a record from its source (technique) or attack (blast) and appends it; nothing while time is stopped. */
void EftHit_Add(EftHitRec *rec);

/* Start of a frame: empties the list and rewinds the arena, unless time is stopped. */
void EftHit_BeginFrame(void);

/* Empties the list and rewinds the arena. */
void EftHit_Clear(void);

/* Returns the record list. */
EftHitList *EftHit_GetList(void);

/* Returns the flags of the task that owns record idx (0 when there is none). */
s32 EftHit_GetTaskFlags(u32 idx);

/* Reports an event of record idx to its task: ors bits into the task's flags and stores where it happened. */
/* (Matches only with the two tests nested, the global used directly and `rec` assigned inside: a local for the list
 * or `rec` computed up front changes the order of the by-value vector's entry copy.) */
void EftHit_SetTaskFlag(u32 idx, s32 bits, EftVec pos);

/* Spawns the impact effect of every record whose task was hit this frame, once per task. */
void EftHit_SpawnImpacts(void);

/* Tells the hit detection whether the record may still hit in pass `mode` (0, 1 or 2). */
s32 EftHit_CanHit(EftHitRec *rec, s32 mode);

/* 0 for a technique of class 0 kind 4, or of another class and kind 9 or 7; else 1. */
/* (An if / else on the class with `kind == 9 || kind == 7` in one condition; a switch on the class, or two separate
 * `if`s for 9 and 7, compile to other code.) */
s32 EftHit_IsStoppedByHit(EftHitRec *rec);

/* Lets a multi-hit technique spawn an impact effect again on its next hit. */
s32 EftHit_RearmImpact(EftHitRec *rec);

/* Clash of two technique records: 4 = head-on (beam struggle), 1 / 2 = which one is passed, 3 = no clash rule. */
/* A head-on pair (a moves toward b's previous position and the two movements oppose) stops the technique timers of
 * fighters 0 and 1 by literal id (EftTechEvt_RequestStop), whoever owns the records; the caller does not gate this
 * by contact. The kind test is a range test on the signed byte (`kind >= 0 && kind <= 2`) in an `if` of its own:
 * that is what gives lbu / sltiu and the later sign extension. */
s32 EftHit_ClashTech(EftHitRec *a, EftHitRec *b);

/* Compares the levels of two records: 2 = a is stronger, 1 = b is stronger, 3 = equal. */
static inline s32 EftHit_CompareLevel(EftHitRec *a, EftHitRec *b);

/* Clash of two records: 1 = b wins, 2 = a wins, 3 = draw, 4 = beam struggle. */
s32 EftHit_Clash(EftHitRec *a, EftHitRec *b);

/* Returns 1 when the owning task is a multi-hit technique. */
s32 EftHit_IsMultiHit(EftHitRec *rec);

/* Counts one more hit of the owning task. */
void EftHit_IncHitCount(EftHitRec *rec);

/* Returns the number of hits the owning task has landed. */
s32 EftHit_GetHitCount(EftHitRec *rec);

/* Returns the technique definition's hit limit (0 for a blast). */
s32 EftHit_GetMaxHits(EftHitRec *rec);

/* Returns byte 0xB of the technique definition (0 for a blast). */
s32 EftHit_GetDefUnkB(EftHitRec *rec);

/* Increments the owning task's counter A. */
void EftHit_IncCountA(EftHitRec *rec);

/* Sets the owning task's counter A. */
void EftHit_SetCountA(EftHitRec *rec, s32 value);

/* Returns the owning task's counter A. */
s32 EftHit_GetCountA(EftHitRec *rec);

/* Returns 1 for a technique whose definition has flag 0x20. */
s32 EftHit_HasDefFlag20(EftHitRec *rec);

/* Flags the record as the last hit of its technique. */
void EftHit_MarkLastHit(EftHitRec *rec);

/* Returns 1 for a technique whose definition has flag 0x200000. */
s32 EftHit_HasDefFlag200000(EftHitRec *rec);

/* Calls 0x177BC8 on the task of blast record idx. */
s32 EftHit_NotifyBlastTask(u32 idx, void *mtx);

/* Returns 1 for a technique of class 0 kind 4, or of another class and kind 9. */
s32 EftHit_IsRushHit(EftHitRec *rec);

/* Returns the radius of the shape's first volume. */
f32 EftHit_GetRadiusA(EftHitRec *rec);

/* Returns the radius of the shape's second volume. */
f32 EftHit_GetRadiusB(EftHitRec *rec);

/* Sets the radius of the shape's first volume. */
void EftHit_SetRadiusA(EftHitRec *rec, f32 radius);

/* Sets the radius of the shape's second volume. */
void EftHit_SetRadiusB(EftHitRec *rec, f32 radius);

/* Flags (task flag 0x10) every record that left the stage radius and pulls its task position back onto it. */
void EftHit_ClampToStage(void);

/* Stores this frame's result code in the task of every record. */
void EftHit_UpdateResults(void);

/* Turns the task's event flags into the result code its update reads: 0 none, 1, 3, 4 = hit, 5 = finished. */
s32 EftHit_CalcResult(EftHitRec *rec);

/* Allocates the arena header and its 0x1800-byte buffer. */
void EftHitArena_Init(void);

/* Frees the arena buffer and header. */
void EftHitArena_Term(void);

/* Rewinds the arena. */
void EftHitArena_Reset(void);

/* Takes n bytes of the arena: a post-increment of the cursor seen as a pointer to an n-byte object. */
#define EFT_ARENA_ALLOC(n) ((void *)(*(u8 (**)[n])&gEftHitArena->cur)++)

/* Takes 0x20 bytes of the arena (no caller). */
void *EftHitArena_Alloc20A(void);

/* Takes 0x20 bytes of the arena (no caller). */
void *EftHitArena_Alloc20B(void);

/* Takes 0x40 bytes of the arena (no caller). */
void *EftHitArena_Alloc40(void);

/* Takes a 0x20-byte sphere of the arena. */
EftHitSphere *EftHitArena_AllocSphere(void);

/* Takes 0x20 bytes of the arena (no caller). */
void *EftHitArena_Alloc20C(void);

/* Takes a record (0x190 bytes) of the arena (no caller). */
EftHitRec *EftHitArena_AllocRec(void);

/* Takes a 0x30-byte box of the arena. */
EftHitBox *EftHitArena_AllocBox(void);

/* Sets a type 3 shape (no caller). */
void EftHit_SetShape3(EftHitRec *rec, void *a, void *b);

/* Sets a type 4 shape (no caller). */
void EftHit_SetShape4(EftHitRec *rec, void *a, void *b);

/* Sets a type 5 shape (no caller). */
void EftHit_SetShape5(EftHitRec *rec, void *a, void *b);

/* Sets the shape to two spheres: previous and current position. */
void EftHit_SetShapeSpheres(EftHitRec *rec, EftHitSphere *a, EftHitSphere *b);

/* Sets a type 6 shape (no caller). */
void EftHit_SetShape6(EftHitRec *rec, void *a, void *b);

/* Sets a type 2 shape (no caller). */
void EftHit_SetShape2(EftHitRec *rec, void *a, void *b);

/* Sets the shape to two boxes: previous and current position. */
void EftHit_SetShapeBoxes(EftHitRec *rec, EftHitBox *a, EftHitBox *b);

/* Returns 1 for a technique whose definition class is cls. */
s32 EftHit_IsTechClass(EftHitRec *rec, s32 cls);

/* Returns the record's scale: the definition's for a technique, 0.1 for a blast. */
f32 EftHit_GetScale(EftHitRec *rec);

/* Marks the owning task as multi-hit when the definition has a hit limit, and drops a stale "hit a fighter". */
/* FAKE MATCH (permuter): the self-assignment of the definition's count inside the `if`. It emits nothing in the
 * end, but the store (`sb count,10(def)`) is real RTL until AFTER register allocation: only the cse pass that
 * follows reload deletes it, as a store of a value the register was just loaded with. Until then the definition
 * pointer and the count are live into the inner block, so they are no longer two values local to the middle block
 * with equal priority (2 references, a life of one instruction: the tie went to the first-born, the definition,
 * which took $v0 and pushed the count to $v1). Without the statement 3 of 20 instructions differ, registers only:
 * the original keeps rec->src in $v0 and loads the definition into $v1 (lw v1,0x24(v0); lb v0,0xA(v1)).
 * `+= 0`, `|= 0`, `*= 1` and a clamp the compiler folds away (`x = x > 127 ? 127 : x` on the s8 field) do the
 * same; a second READ of the field (a dead local, `(void)`, an empty `if`, `n` loaded again) does not, and
 * `... = n` emits a real store (n is the sign-extended copy).
 * What it stands for is unknown: a statement of the original that wrote the count back unchanged (a vacuous
 * clamp or a macro), or anything else that kept the two values alive in the inner block. About 130 natural forms
 * were tried in the earlier passes (locals for each value, a variable set twice, early returns, && / nested,
 * inline accessors, result variables, casts, loop / goto / switch shapes): all give those 3 instructions or more. */
void EftHit_InitMultiHit(EftHitRec *rec);

/* Spawns the impact effect of a ki blast at the place its task was hit. */
void EftHit_SpawnBlastImpact(EftHitRec *rec);

/* Spawns the impact effect of a technique: on a fighter (definition impactFx) or on the stage (groundFx). */
void EftHit_SpawnTechImpact(EftHitRec *rec);

/* Allocates and clears the camera cut state. */
void EftCam_Init(void);

/* Frees the camera cut state. */
void func_001A55B0(void) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftCam);
    gEftCam = NULL;
}

/* Clears the camera cut state (BtlScene_Reset). */
void EftCam_Clear(void);

/* Starts a camera cut: plays arg->anim on the demo camera, timed by fighter arg->objId's technique timer if any. */
void EftCam_Start(EftCamArg *arg);

/* Sets whether the cut holds its last frame instead of ending. */
void EftCam_SetHold(s32 hold);

/* Pauses or resumes an active cut. */
void EftCam_SetPaused(s32 paused);

/* Returns the pause state of the cut. */
s32 EftCam_IsPaused(void);

/* Returns 1 while a cut is playing. */
s32 EftCam_IsActive(void);

/* Ends the cut and releases the demo camera. */
void EftCam_Stop(void);

/* Per-frame: moves the cut to the fighter's technique time (or 2.0 further) and ends it past the animation's length. */
void EftCam_Update(void);

/*
 * Lights a 256-entry palette (RGBA bytes) from a 256-entry table of normals (bytes, 128 = 0): adds the colour
 * (r, g, b) to every entry and puts the diffuse term (N.L * 64 + 32, at most 128) into alpha.
 */
void EftGfx_LightClutDiffuse(u8 *dst, u8 *nrm, EftVec light, u8 r, u8 g, u8 b);

/* Adds a specular highlight to a 256-entry palette from the table of normals: view matrix, light matrix, eye vector. */
void EftGfx_LightClutSpecular(u8 *dst, u8 *nrm, EftMtx view, EftMtx light, EftVec eye, f32 power);

/* Blends two 256-entry palettes: dst = a * t + b * (1 - t), t clamped to 0..1 (no caller). */
void EftGfx_LerpClut(u8 *dst, u8 *a, u8 *b, f32 t);

/* Builds the tangent frame of a triangle from its three positions and three texture coordinates. */
void EftMath_CalcTangentFrame(EftMtx *out, EftVec *pos, EftVec *uv);

/* Builds the rotation whose Z axis is dir (up = -Y), rolled by `roll` about Z; returns 0 for a null dir. */
s32 EftMath_MtxFromDir(EftMtx *out, EftVec *dir, f32 roll);

/* Wraps an angle into -pi..pi. */
f32 EftMath_WrapAngle(f32 angle);

/* Catmull-Rom point of four control points at t. The result goes to a by-value argument and is lost (no caller). */
void EftMath_CatmullRom(EftVec out, EftVec *p, f32 t);

/* Quadratic spline point of three control points at t (basis 0x2EC520), w = 1. */
void EftMath_Spline3(EftVec *out, EftVec *p, f32 t);

/* Quadratic spline point of three control points at t (basis 0x2EC560); result lost in a by-value argument (no caller). */
void EftMath_Spline3B(EftVec out, EftVec *p, f32 t);

/* Cubic Bezier point of four control points at t; result lost in a by-value argument (no caller). */
void EftMath_Bezier(EftVec out, EftVec *p, f32 t);

/* Linear interpolation of two points; result lost in a by-value argument (no caller). */
void EftMath_Lerp(EftVec out, EftVec *p, f32 t);

/* Kochanek-Bartels (tension, bias, continuity) spline point of four control points; result lost (no caller). */
void EftMath_TcbSpline(EftVec out, EftVec *p, f32 t, f32 tension, f32 bias, f32 continuity);

/* Returns the five view-frustum planes (world space) the clipped draw functions use. */
EftVec *EftGfx_GetClipPlanes(void);

/* Rebuilds the five clip planes from the current camera view (top, bottom, left, right, near). */
void EftGfx_UpdateClipPlanes(void);

/* Direction a projectile of fighter objId starts in: at the locked target, else straight ahead (yaw only). */
s32 EftAim_GetDir(EftVec *out, s32 arg, s32 objId);

/*
 * Same for a technique: with definition aimMode != 0 the aim is taken once and kept in src->aimDir; an aim more
 * than 60 degrees off the fighter's facing (flat dot < 0.5) falls back to straight ahead.
 */
s32 EftAim_GetDirKeep(EftHitSrc *src, EftVec *out, s32 arg, s32 objId);

/* Rotates v about a unit axis by angle (Rodrigues' formula); w is copied from v. */
void EftMath_RotateAboutAxis(EftVec *out, EftVec *v, EftVec *axis, f32 angle);

/*
 * Homing: turns dir towards the opponent of objId by at most maxTurn radians. The target is the opponent's node
 * 0x11 led by half of its frame movement times the frames to impact (distance / speed, at most 15); a target
 * behind the projectile (dot <= 0) leaves dir unchanged, and so does a fighter that is not locked on.
 */
void EftAim_Home(EftVec *out, EftVec *pos, EftVec *dir, s32 objId, f32 speed, f32 maxTurn);

/* One projected vertex as ClipPoly_ProjectCur writes it (fixed-point screen x, y, depth, w). */
typedef struct EftGfxScr {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
    /* 0xC */ s32 w;
} EftGfxScr;

/*
 * Draws a polygon (3 vertices on entry, up to 9 after clipping against the five view planes) as a fan of textured
 * triangles (0x132E80). The sort depth of each triangle is the average of its three projected depths >> 8
 * (mirrored to 0x1000 - z when flip is set) plus zOfs; depths are clamped to 0xFFFFFF.
 */
void EftGfx_DrawPolyAvgZ(EftGfxVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 flip, u64 tex, s32 zOfs);

/* Same with a fixed sort depth z (mirrored when flip is set); front forces the three depths to 0xFFFFFF. */
void EftGfx_DrawPolyFixedZ(EftGfxVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex, s32 z);

/* Same as EftGfx_DrawPolyAvgZ with the option to force the three depths to 0xFFFFFF (front). */
void EftGfx_DrawPolyAvgZFront(EftGfxVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex,
                              s32 zOfs);

/* Same with the average depth multiplied by zScale. */
void EftGfx_DrawPolyScaledZ(EftGfxVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex,
                              f32 zScale);

/* GS XYZF2 register. */
typedef struct EftGfxXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftGfxXyzf;

typedef struct EftGfxRgbaq {
    u8 r, g, b, a;
    f32 q;
} EftGfxRgbaq;

typedef struct EftGfxSt {
    f32 s, t;
} EftGfxSt;

/* DMA tag + REGLIST GIF tag (14 registers): PRIM, TEX0, four (RGBAQ, ST, XYZF2): one gouraud textured strip
   (the same packet as EftBStripPkt of eft_b.c). */
typedef struct EftGfxStripPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000008: NEXT, 8 quadwords */
    /* 0x04 */ struct EftGfxStripPkt *next;
    /* 0x08 */ u32 vif0;         /* 0x10000000 */
    /* 0x0C */ u32 vif1;         /* 0x50000008: DIRECT, 8 quadwords */
    /* 0x10 */ u64 gifTag;       /* 0xE400000000008001: NLOOP 1, EOP, REGLIST, 14 registers */
    /* 0x18 */ u64 regs;         /* 0x42142142142160; + 0x10 for context 2 (TEX0_1 becomes TEX0_2) */
    /* 0x20 */ u64 prim;         /* 0x5C (gouraud textured triangle strip, alpha blended) | context << 9 */
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftGfxRgbaq rgbaq0;
    /* 0x38 */ EftGfxSt st0;
    /* 0x40 */ EftGfxXyzf xyz0;
    /* 0x48 */ EftGfxRgbaq rgbaq1;
    /* 0x50 */ EftGfxSt st1;
    /* 0x58 */ EftGfxXyzf xyz1;
    /* 0x60 */ EftGfxRgbaq rgbaq2;
    /* 0x68 */ EftGfxSt st2;
    /* 0x70 */ EftGfxXyzf xyz2;
    /* 0x78 */ EftGfxRgbaq rgbaq3;
    /* 0x80 */ EftGfxSt st3;
    /* 0x88 */ EftGfxXyzf xyz3;
} EftGfxStripPkt; /* size 0x90 */

extern s32 Vu0Cur_ProjectPoint(EftGfxScr *out, EftVec *pos); /* projects a point to GS 12.4 screen x, y, depth, w */
extern void Vec4_Mul(EftVec *dst, EftVec *a, EftVec *b);      /* per-component product */
extern void Vec4_ToInt(EftGfxScr *dst, EftVec *src);          /* float vector to fixed point */
extern s32 EftPrim_IsOffScreen(s32 x, s32 y, s32 z);          /* eft_b.c: outside the GS drawing area */

/*
 * Draws a camera-facing textured quad at a world position, written straight into the display list.
 *   - pos->w = 1; Vu0Cur_ProjectPoint projects pos into fixed-point screen x, y, z, w. The half size in pixels is
 *     (s32)w (h) * (s32)(gBtlCamView + 0x234 (screen distance) * 4096 / screen w) >> 12; nothing is drawn below 2
 *     pixels in either direction.
 *   - the two corner offsets (w, h) and (-w, h) are rotated about Z by rot (Mtx_StoreIdentity + Mtx_RotateZ),
 *     scaled by the aspect vector (1, 7/6, 1, 1) and converted to fixed point; the quad is dropped when any of the
 *     four corners centre -/+ a, centre +/- b is off screen (EftPrim_IsOffScreen).
 *   - takes 0x90 bytes at gOtCur: a 4-vertex gouraud textured, alpha-blended triangle strip (context 2 when
 *     layer >= 2), TEX0 = tex0, per vertex RGBAQ (the four floats of color converted to bytes, q = 1), ST
 *     ((u0,v0), (u0,v1), (u1,v0), (u1,v1)) and XYZF2 (centre - a, centre + b, centre - b, centre + a; depth
 *     forced to 0xFFFFFF when front is set; fog 0xFF).
 *   - links the packet into the ordering table at depth slot (projected z >> 8, taken BEFORE front is applied,
 *     clamped to 0..0xFFF) and chain layer (layer - 2 for layers >= 2).
 * It reads the camera view only and writes nothing but pos->w and display-list memory.
 * The parameter order (floats in front of layer / front / tex0) is the one three callers declare (eft_aa.c,
 * eft_ab_c.c, eft_c.c); it decides which saved float register u1 and v1 get.
 */
void EftGfx_DrawSprite(EftVec *pos, EftVec *color, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot, s32 layer,
                       s32 front, u64 tex0);
