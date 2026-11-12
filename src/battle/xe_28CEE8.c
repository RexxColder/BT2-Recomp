/*
 * Stage rigid bodies (0x22FD10..0x230B38): the list of falling debris pieces. See battle/stg_d.h.
 *
 * Per frame (StgRigid_Update, skipped while the battle is paused):
 *   StgRigidList_BeginFrame   remember the transform, collect nearby triangles (only for bodies with a hit
 *                             buffer), choose the drag
 *   10 sub-steps of 1/60 + 0.00001: StgRigidList_UpdateCenters, StgRigidList_Collide, StgRigidList_AddForces
 *                             (gravity + drag), StgRigidList_Step
 *   StgRigidList_EndFrame     clamp to the stage radius, rest test
 * Every pass walks the active list in creation order; bodies do not interact with each other.
 */
#include "common.h"
#include "sys/math3d.h"
#include "sys/heap.h"
#include "sys/randf.h"
#include "sys/rigid.h"
#include "battle/stg_d.h"

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sqrtf(f32 x);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void ColSphere_Set(RigidSphere *out, Vec4 *center, f32 radius);        /* fills a sphere */
extern s32 ColSphere_TestTri(Vec4 *out, RigidSphere *sphere, StgRigidTri *tri);    /* sphere against triangle: closest point */
extern void StgCol_CollectSphere(RigidSphere *sphere, s32 hits);                     /* collects the stage triangles near a sphere */

extern s32 BtlStage_IsReady(void);
extern f32 BtlStage_GetInnerRadius(void);
extern s32 BtlStage_GetWaterLevel(f32 *level);

/* Length of one sub-step. The constant is 0x3C889D80 (0.016676664): 1 / 60 plus a little, so that ten steps pass
   the 1 / 6 limit of StgRigid_Update. (1.0f / 60.0f * 1.0006f gives the same bits.) */
#define STG_RIGID_DT (1.0f / 60.0f + 0.00001f)

/* The two list helpers in front of this file. */
extern s32 StgRigidList_Count(StgRigidNode *head);       /* number of nodes */
extern StgRigidNode *StgRigid_AllocNode(void);          /* a free node, NULL when the pool is used up */

/* Local view of the battle work: only the flag word. */
typedef struct StgRigidWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags;       /* 0x100: paused */
} StgRigidWork;
extern StgRigidWork *Battle_GetWork(void);


/* Makes a box empty (min = +1e10, max = -1e10) so that points can be added to it. First of the box helpers. */
void StgAabb_SetEmpty(StgAabb *box) {
    f32 big = 1e10f;

    box->min[0] = big;
    box->min[1] = big;
    box->min[2] = big;
    box->max[0] = -big;
    box->max[1] = -big;
    box->max[2] = -big;
}
