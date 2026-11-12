/*
 * Battle stage, first part, continued: 0x240DB8..0x242D28 (split from stg_a.c at integration, around the three
 * VU0 macro-code rotations at 0x240C68..0x240DB8, which stay an assembly chunk; see the note at the end of stg_a.c).
 * Debris pieces, destructible objects, stage change, paths, file binding, placements, getters.
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

/* Both are defined in stg_a.c, the first half of the same original source file, so the original compiler had seen
 * their bodies before it reached the callers here and knew what they touch. The attributes stand in for that:
 * Stg_WrapRange is pure arithmetic on its arguments (StgPart_Animate only matches when its calls are scheduled as
 * calls that read and write no memory); StgNode_IsRigid only reads memory (BtlStage_UpdateObjs). */
extern f32 Stg_WrapRange(f32 lo, f32 hi, f32 v) __attribute__((const));
extern s32 StgNode_IsRigid(StgNode *node) __attribute__((pure));


/* Node matrix = rotation X, Y, Z then translation, through the VU0 matrix registers; returns the position. */
#define STG_NODE_BUILD()                          \
    Vu0Cur_LoadIdentity();                              \
    StgVu_RotateX(rot.x);                         \
    StgVu_RotateY(rot.y);                         \
    StgVu_RotateZ(rot.z);                         \
    Vu0Cur_Translate(&pos);                          \
    Vu0Cur_StoreMtx(node);                          \
    Vec4_Copy(out, (Vec4 *)node->mtx.m[3])

#define STG_ANGLE(deg) Stg_WrapRange(-3.14159265f, 3.14159265f, (deg) * 3.14159265f / 180.0f)


/* Ground under pos: finds its zone (starting from `zone`) and asks the collision code (StgGround_Probe) for the
 * ground point of a unit box around pos. Returns the zone; out is untouched while the stage is not ready. */
s32 BtlStage_ProbeGround(s32 zone, Vec4 *pos, StgGroundHit *out) {
    StgBox box;
    StgVec16 ext = { 1.0f, 1.0f, 1.0f, 1.0f };
    StgVec16 *e = &ext;
    s32 r;

    if (!BtlStage_IsReady()) {
        return zone;
    }
    memset(out, 0, sizeof(StgGroundHit));
    r = BtlStage_FindZoneNear(zone, pos);
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    ColBox_SetCenterHalf(&box, pos, e);
    StgGround_Probe(r, &box, out, box.min[1]);
    return r;
}
