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

/* Poses a debris piece at `frame` of its key animation (position linear, angles through +3600 so that they
 * interpolate the short way), stores the matrix in its node and returns the position. Does nothing when the
 * frame falls between no pair of keys. */
void StgPart_Animate(StgPart *part, f32 frame, Vec4 *out);

/* Material of an object for its break effects: 0, 1 or 2 from type bits 0, 1, 2. */
#define STG_MATERIAL_OF(obj) \
    if ((obj)->type & STG_OBJ_MAT0) { \
        return 0; \
    } \
    if ((obj)->type & STG_OBJ_MAT1) { \
        return 1; \
    } \
    if ((obj)->type & STG_OBJ_MAT2) { \
        return 2; \
    } \
    return 0

/* Dust of a breaking object: -1 for none, else its material; *scale = 0.7 for the small kind, else 1. */
s32 StgObj_GetDust(StgObj *obj, f32 *scale);

/* Material of an object: 0, 1 or 2. */
s32 StgObj_GetMaterial(StgObj *obj);

/* For an object that may hold the hidden item: copies the position of object definition 0, returns 1. */
s32 StgObj_GetItemPos(Vec4 *out, StgObj *obj, s32 idx);

/* Bit 0 of a part's flags, for a part that may be missing. The two variables (the pointer that is tested and
 * the one that is used) are what the original code generation shows: p is loaded into v0, then copied. */
#define STG_PART_SET(part)        \
    p = (part);                   \
    if (p != NULL) {              \
        q = p;                    \
        q->flags |= 1;            \
    }
#define STG_PART_CLEAR(part)      \
    p = (part);                   \
    if (p != NULL) {              \
        q = p;                    \
        q->flags &= ~1;           \
    }

/* Breaks object idx and, recursively, every object that names it as parent: swaps the whole model for the
 * broken one, starts the debris animation, shakes cameras and pads near it. Returns 0 if it was already broken. */
s32 BtlStage_BreakObj(s32 idx, Vec4 *hitPos, StgBreakInfo *info);

/* Puts every object in one state: broken != 1 restores them whole (hit points, type and parent reloaded from the
 * stage data); broken == 1 marks them all broken without any animation. */
void BtlStage_ResetObjs(s32 broken);

/* Breaks object idx for the fighter / effect objId (< 0: nobody), with the break sound. In mode 1, when the
 * rule holds a hidden item and the object is an item holder, one rand() draw in 8 awards it. Always returns 1. */
s32 BtlStage_DestroyObj(s32 objId, s32 idx, Vec4 *hitPos);

/* 1 when object idx is broken. */
s32 BtlStage_IsObjBroken(s32 idx);

/* Takes `damage` hit points from object idx; 1 when it has none left (the caller then breaks it). 0 if broken. */
s32 BtlStage_DamageObj(s32 idx, s32 damage);

/* Type bits of object idx, 0 once it is broken. */
s32 BtlStage_GetObjType(s32 idx);

/* Per frame (not while paused): advances the debris of every object that is falling. */
/* Written as the original was, which the code generation shows: the object is indexed (`objs[i]`) at every use
 * instead of through an element pointer (the compiler then keeps several copies of that pointer and runs out of
 * saved registers: the index and its byte offset live on the stack), `first` is set in both arms of an if / else,
 * and the dust cases 0 and 1 are separate although identical. */
void BtlStage_UpdateObjs(void);

/* Asks the loader for the stage this one changes into (BtlStage_GetChangeTarget). */
void BtlStage_RequestChange(void);

/* Finds the path table in the stage file (header entry 24) and relocates it. */
void BtlStage_BindPaths(void);

/* Empty. */
void BtlStage_PathStub(void);

/* Forgets the path table. */
void BtlStage_ClearPaths(void);

/* Number of stage paths, 0 before the table is bound. */
s32 BtlStage_GetPathCount(void);

/* Stage path n, NULL when out of range. */
StgPath *BtlStage_GetPath(s32 n);

/* Stage path 0 (no caller). */
StgPath *BtlStage_GetPath0(void);

static inline void Stg_Normalize(Vec4 *v);

/* Yaw that faces from (x0, z0) to (x1, z1), in -pi..pi. */
f32 Stg_CalcYaw(f32 x0, f32 z0, f32 x1, f32 z1);

/* Relocates the three point lists of the "MEF0" block and negates y and z of every point. */
void BtlStage_BindMef(void);

#define STG_RELOC(field) d->field = (void *)((u8 *)base + (s32)d->field)

/* Binds the stage parameter block: turns its offsets into pointers and negates y and z of every position. */
void BtlStage_BindData(BtlStage *stage, StgDataA *base);

/* Binds the three blocks of the stage file to the stage, once per file. */
void BtlStage_BindFile(BtlStage *stage);

/* Water: returns 1 and the level when the stage has water, else 0 and 0. Keeps the last answer while the stage
 * is not ready. */
s32 BtlStage_GetWaterLevel(f32 *level);

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

/* Start placement of a player: the stage's start point for `side` (the single alternative point when alt == 1),
 * dropped onto the ground from y = -700, with the yaw that faces the point's target. Returns the zone of the
 * point (the fighter keeps it as its "area"). Reads gBtlStage->data even when the stage is not ready. */
s32 BtlStage_GetStartPlace(s32 side, Vec4 *pos, Vec4 *rot, s32 alt);

/* The stage's third placement (StgDataA +0x3C, first entry), dropped onto the ground like a start placement;
 * returns its zone. The fighter uses it for the placement requests 0xF4 / 0xF6 / 0xF7. */
s32 BtlStage_GetPlace(Vec4 *pos, Vec4 *rot);

/* First vector of the stage light; the last one read while the stage is not ready. */
void BtlStage_GetLightVecA(Vec4 *out);

/* Second vector of the stage light (the battle object light direction); the last one read while not ready. */
void BtlStage_GetLightVecB(Vec4 *out);

/* Reloads an object's hit points, type and parent from its definition. */
void StgObj_LoadDef(StgObj *obj, s32 idx);

/* Object definition idx, NULL when out of range. */
StgObjDef *BtlStage_GetObjDef(s32 idx);

/* Entry idx of the list at StgDataA +0x44, NULL when out of range. */
StgVec *BtlStage_GetList40(s32 idx);

#define STG_LIST_GETTER(name, count, list)   \
    void *name(void) {                       \
        StgDataA *d;                          \
                                             \
        if (gBtlStage == NULL) {             \
            return NULL;                     \
        }                                    \
        d = gBtlStage->data;                 \
        if (d == NULL) {                     \
            return NULL;                     \
        }                                    \
        if (d->count > 0) {                  \
            return d->list;                  \
        }                                    \
        return NULL;                         \
    }

/* The lists of the stage data that have no index: the pointer when the count is positive, else NULL. */










