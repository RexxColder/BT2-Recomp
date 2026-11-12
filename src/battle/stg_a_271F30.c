/*
 * Battle stage, first part: 0x23FB20..0x242D28 (include/battle/stg_a.h has the layouts).
 *
 * What is here, in address order:
 *   0x23FB20  offset tables of the stage file (used by the stage model code at 0x115290 / 0x115478)
 *   0x23FBF8  the stage object gBtlStage: ready test, init / reset / term
 *   0x23FD00  a stage viewer's helpers (StgDbg_*, no caller in the game; one rand() draw)
 *   0x23FDB0  zones (rectangles on the ground plane) and the three bounds a fighter is clamped to
 *   0x240168  culling for the stage draw: frustum, box and sphere tests
 *   0x240940  more of the stage viewer (file request / free)
 *   0x240AB8  debris pieces of destructible objects: key animation or rigid body
 *   0x241238  destructible objects: damage, break (recursive over children), reset, per-frame update
 *   0x241E38  stage change request, stage paths
 *   0x241F10  binding of the stage file (offsets to pointers, y and z negated), water level, ground probe,
 *             start placements, light vectors, getters of the stage data sections
 *
 * Simulation or drawing: see the comment on each function. In short the fight reads from this file the bounds
 * (radius, top, bottom), the zone of a position, the ground height under a start placement, the water level,
 * the start placements, the stage paths and the state of the destructible objects (hit points, broken or not,
 * type bits). The frustum functions, the fades, the light vectors and the debris animation only feed drawing,
 * except that debris pieces of rigid kind are handed to the stage rigid bodies (battle/stg_d.c).
 *
 * Every C function matches. Not C: the three VU0 macro-code rotations (hand-written assembly in the original),
 * which stay an assembly chunk between this file and stg_a_b.c.
 */
#include "common.h"
#include "sys/math3d.h"
#include "sys/common.h"
#include "sys/heap.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "battle/stg_a.h"

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sqrtf(f32 x);
extern f32 atan2f(f32 y, f32 x);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *out, Vec4 *v, f32 s);
extern void Vec3_Scale(Vec4 *out, Vec4 *v, f32 s);
extern void Vec3_Normalize(Vec4 *out, Vec4 *v);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Mtx_MulVec4(Vec4 *out, Mtx44 *m, Vec4 *v);
extern void Vec4_Div(Vec4 *out, Vec4 *v, f32 d);      /* out = v / d */
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);         /* matrix copy */
extern void Vu0Cur_LoadIdentity(void);                           /* VU0: current matrix = identity */
extern void Vu0Cur_Translate(Vec4 *pos);                      /* VU0: translate the current matrix */
extern void Vu0Cur_StoreMtx(void *m);                        /* VU0: store the current matrix */

extern void *File_Request(s32 id, void *buf, s32 arg);
extern void StreamSe_PlayDefault(s32 se, s32 id);
extern void BtlCharApi_PlaySoundAt(Vec4 *pos, s32 kind, s32 id, f32 near, f32 far);
extern void BtlCharApi_RumbleNear(Vec4 *pos, f32 near, f32 far, f32 power, f32 time);
extern void BtlCharApi_ShakeCamsNear(Vec4 *pos, f32 near, f32 far, f32 power, f32 time);
extern s32 BtlCharApi_IsInputInjected(s32 objId);

/* Stage model code (0x114C60..0x115DE0) and stage code after this file. */
extern void BtlStage_Relocate(void *arg);
extern void StgModel_InitStage(void);
extern void StgModel_ResetAnims(void);
extern void StgModel_BindAnims(void);
extern void StgModel_ClearAnims(void);
extern void ColMesh_SetBase(void *arg);
extern void StgRigid_Reset(void);                           /* stage rigid bodies: reset */
extern void StgRigid_Init(void);                           /* stage rigid bodies: init */
extern void StgRigid_Term(void);                           /* stage rigid bodies: term */
extern s32 StgRigid_Create(Vec4 *pos, f32 radius, s32 arg);  /* new rigid body, handle or < 0 */
extern void StgRigid_Launch(s32 body, Vec4 *hitPos, s32 material);
extern void StgRigid_Release(s32 body);                       /* release a rigid body */
extern void StgRigid_GetMatrix(StgNode *node, s32 body);        /* node matrix = body transform */
extern void ColBox_SetCenterHalf(StgBox *out, Vec4 *center, StgVec16 *extent); /* box = center +- extent */
extern void StgAmb_Start(void);
extern void StgAmb_Stop(void);
extern s32 BtlStage_GetChangeTarget(void);
extern void StgFx_Reset(void);
extern void StgGround_Probe(s32 zone, StgBox *probe, StgGroundHit *out, f32 y);
extern void StgNav_UnblockObj(s32 idx);
extern void HudTimer_ShowMark(void);
extern void EftGndDust_SpawnDebris(Vec4 *pos, f32 a, f32 b, f32 scale); /* dust effect */
extern void EftWater_AddSplashAt(Vec4 *pos, f32 size);                /* splash effect */

extern s32 gStgDbgState;       /* gStgDbgState */
extern s32 gStgDbgUnk;         /* gStgDbgUnk */
extern s32 gStgDbgExternFile;  /* gStgDbgExternFile */
extern StgPathTable *gStgPaths; /* gStgPaths */
extern StgMef *gBtlStageFxRes;        /* gBtlStageFxRes */
extern s32 gStgHasWater;       /* gStgHasWater */
extern f32 gStgWaterY;         /* gStgWaterY */
extern f32 gStgLastRadius;     /* gStgLastRadius */
extern f32 gStgLastTop;        /* gStgLastTop */
extern f32 gStgLastBottom;     /* gStgLastBottom */
extern StgPlace gStgDbgPlaces[6]; /* gStgDbgPlaces */
extern Vec4 gStgLastLightVecA; /* gStgLastLightVecA */
extern Vec4 gStgLastLightVecB;  /* gStgLastLightVecB */
extern Vec4 D_002EC2C0;        /* zero vector */
extern StgView *gBtlCamView;

#define STG_RES ((BattleRes *)gCommonRes->unk20)

void StgDbg_ClearState(void);
void StgDbg_BindFile(void);
void StgVu_RotateZ(f32 angle);
void StgVu_RotateX(f32 angle);
void StgVu_RotateY(f32 angle);

/* Turns the file-relative offsets of an offset table into pointers, once. */
void StgOfsTable_Relocate(StgOfsTable *t) {
    s32 i;

    if (t->relocated == 0) {
        for (i = 0; i < t->count; i++) {
            t->entries[i] += (s32)t;
        }
        t->relocated = 1;
    }
}

/* Entry i of an offset table, 0 when out of range. */
s32 StgOfsTable_Get(StgOfsTable *t, s32 i) {
    if (i < t->count) {
        return t->entries[i];
    }
    return 0;
}

/* Number of entries of an offset table. */
s32 StgOfsTable_GetCount(StgOfsTable *t);

/* Turns the offsets of the path table (the list and each path's points) into pointers, once. */
void StgPathTable_Relocate(StgPathTable *t);

/* 1 when there is a stage, no stage load job is running and the stage is not flagged "not ready". */
s32 BtlStage_IsReady(void);

/* Binds the stage file if needed and puts every destructible object back whole. */
void BtlStage_Reset(void);

/* Sets the stage object, builds its model and rigid bodies, then resets it. */
void BtlStage_Init(BtlStage *stage, void *arg);

/* Drops the stage object. */
void BtlStage_Term(void);

/* Stage viewer (no caller): sets its state. */
void StgDbg_SetState(s32 state);

/* Stage viewer (no caller): binds the loaded stage file. */
void StgDbg_Bind(void);

/* Stage viewer (no caller): one of six fixed placements, picked with rand(). */
void StgDbg_PickRandomPlace(Vec4 *pos, Vec4 *target);

/* Stage viewer (no caller): its state. */
s32 StgDbg_GetState(void);

/* Stage viewer: clears its state. */
void StgDbg_ClearState(void);

/* Tests whether pos (x, z) lies in the rectangle of zone z. */
#define STG_ZONE_OUTSIDE(zone, pos)                           \
    (min.x = (zone).center.x - (zone).half.x,                 \
     min.z = (zone).center.z - (zone).half.z,                 \
     max.x = (zone).center.x + (zone).half.x,                 \
     max.z = (zone).center.z + (zone).half.z,                 \
     max.x < (pos)->x || max.z < (pos)->z || (pos)->x < min.x || (pos)->z < min.z)

/* Index of the first zone whose rectangle contains pos, -1 when none does. */
s32 BtlStage_FindZone(Vec4 *pos);

/* The stage's horizontal radius; the last value read while the stage is not ready. */
f32 BtlStage_GetRadius(void);

/* The radius fighters are kept inside: the stage radius - 100 (not subtracted while the stage is not ready). */
f32 BtlStage_GetInnerRadius(void);

/* The stage's top limit (smallest y). */
f32 BtlStage_GetTop(void);

/* The stage's bottom limit (largest y). */
f32 BtlStage_GetBottom(void);

/* Zone containing pos, trying the given zone and its neighbours first; 0 when no zone contains it. */
s32 BtlStage_FindZoneNear(s32 zone, Vec4 *pos);

/* Zone by index. */
StgZone *BtlStage_GetZone(s32 zone);

/* Clears the mark of every zone. */
void BtlStage_ClearZoneMarks(void);

/* The five plane normals of the frustum (view space, not yet normalised): the sides for a screen distance of
 * 433 and a half height of 224, the half width given as `hz`. Written out in both arms of the test on the view
 * width, as the original was: the compiler merges the common stores after register allocation. */
#define STG_FRUSTUM_PLANES(hz)        \
    fr->plane[0].x = 433.0f;          \
    fr->plane[0].y = 0.0f;            \
    fr->plane[0].z = (hz);            \
    fr->plane[0].w = 1.0f;            \
    fr->plane[1].x = -433.0f;         \
    fr->plane[1].y = 0.0f;            \
    fr->plane[1].z = (hz);            \
    fr->plane[1].w = 1.0f;            \
    fr->plane[2].x = 0.0f;            \
    fr->plane[2].y = 433.0f;          \
    fr->plane[2].z = 224.0f;          \
    fr->plane[2].w = 1.0f;            \
    fr->plane[3].x = 0.0f;            \
    fr->plane[3].y = -433.0f;         \
    fr->plane[3].z = 224.0f;          \
    fr->plane[3].w = 1.0f;            \
    fr->plane[4].x = 0.0f;            \
    fr->plane[4].y = 0.0f;            \
    fr->plane[4].z = 1.0f;            \
    fr->plane[4].w = 1.0f

/* Builds the culling frustum of a view: side plane normals, view matrix, projection. Drawing only. */
void StgFrustum_Build(StgView *view, StgFrustum *fr);

/* Frustum test of the cube (x, y, z) +- r: 0 inside, 1 crossing, 2 outside. Drawing only. */
s32 StgFrustum_TestBox(StgFrustum *fr, f32 x, f32 y, f32 z, f32 r);

/* Signed distance test of the sphere against one side plane: the centre moved along the normal by the radius. */
#define STG_TEST_PLANE(plane)                 \
    pl = (plane);                             \
    Vec4_Scale(&t, pl, part->radius);         \
    Vec4_Add(&t, &v, &t);                     \
    dot = Vec3_Dot(&t, pl)
#define STG_PLANE_RESULT()                    \
    if (dot < 0.0f) {                         \
        in = 0;                               \
    } else {                                  \
        cross = 1;                            \
    }

/* Frustum test of a part's bounding sphere: 0 inside, 1 crossing a side plane, 2 outside. Drawing only. */
s32 StgFrustum_TestPart(StgPart *part, StgFrustum *fr);

/* Stage viewer (no caller): frees the stage file unless it is owned elsewhere. */
void StgDbg_FreeFile(void);

static inline void StgDbg_ResetOnce(void);

/* Stage viewer (no caller): clears its two state words (twice). */
void StgDbg_Reset(void);

/* Stage viewer (no caller): drops the stage and its file. */
void StgDbg_Unload(void);

/* Stage viewer (no caller): requests stage file `id`, freeing the previous one. */
s32 StgDbg_RequestFile(s32 arg, s32 id);

/* Stage viewer: binds the stage data from the loaded file (the battle's own binder). */
void StgDbg_BindFile(void);

/* 1 when a node has a single key: its piece is moved by a rigid body. */
s32 StgNode_IsRigid(StgNode *node);

/* (b - a) / 30 when the difference is under 30, else 1. Used by the stage draw at 0x115A78. */
f32 Stg_FadeRatio(f32 a, f32 b);

/* Fades `value` in with the distance from the current camera beyond its near plane: 0 up to 75, full from 100.
 * Reads the camera; used only by the stage draw at 0x115A78. */
f32 Stg_FadeByCamDist(Vec4 *pos, f32 value);

/* Position of a part's node (row 3 of its matrix). */
void StgPart_GetPos(StgPart *part, Vec4 *out);

/* Wraps v into lo..hi by adding or subtracting the span. */
f32 Stg_WrapRange(f32 lo, f32 hi, f32 v);

/* The three VU0 macro-code rotations StgVu_RotateZ / X / Y (0x240C68..0x240DB8, hand-written assembly in the
 * original) follow here as an assembly chunk; the file continues in stg_a_b.c. They cannot be INCLUDE_ASM:
 * splat writes the VU0 accumulator operand as `ACC` in per-function files, which the assembler rejects. */
