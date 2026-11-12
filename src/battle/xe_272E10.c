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


/* Stage viewer (no caller): one of six fixed placements, picked with rand(). */
void StgDbg_PickRandomPlace(Vec4 *pos, Vec4 *target) {
    s32 n = rand() % 6;

    Vec4_Copy(pos, &gStgDbgPlaces[n].pos);
    Vec4_Copy(target, &gStgDbgPlaces[n].target);
}
