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

/* Last node of a list, NULL when it is empty. */
StgRigidNode *StgRigidList_Last(StgRigidNode *head);

/* The active body with this id, NULL when there is none. */
StgRigidNode *StgRigid_Find(s32 id);

/* Keeps the body inside the stage cylinder: when its horizontal distance from the origin plus its radius exceeds
   the inner radius, x and z are scaled back and both angular velocities are halved. */
void StgRigid_ClampToStage(RigidBody *body);

/* Start of a frame for every body: remembers the transform; a moving body with a hit buffer gets the stage
   triangles near it, and its drag becomes the under-water value when its centre is below the water level. */
void StgRigidList_BeginFrame(StgRigidNode *head);

/* Sub-step, first pass: world-space centre of mass and collision spheres of every moving body. */
void StgRigidList_UpdateCenters(StgRigidNode *head);

/* Sub-step, second pass: a contact force for every collected triangle the body's sphere touches. */
void StgRigidList_Collide(StgRigidNode *head);

/* Sub-step, third pass: gravity and drag on every moving body. */
void StgRigidList_AddForces(StgRigidNode *head);

/* Sub-step, last pass: integrates every moving body over STG_RIGID_DT. */
void StgRigidList_Step(StgRigidNode *head);

/* End of a frame: stage clamp, then the rest test (only bodies with a hit buffer can come to rest). */
void StgRigidList_EndFrame(StgRigidNode *head);

/* Forgets every body: both lists empty, the pool unused. */
void StgRigid_Reset(void);

/* Allocates the pool and numbers its nodes 1..128. */
void StgRigid_Init(void);

/* Frees the pool. */
void StgRigid_Term(void);

/* New body at `pos`, unrotated and at rest, appended to the active list. Returns its id, -1 when the pool is full. */
s32 StgRigid_Create(Vec4 *pos, f32 radius, s32 user);

/* Throws a body: horizontal velocity = `push` (shortened when its squared length exceeds 1200), a random upward
   speed that depends on the material, each component randomly boosted, and a random spin. */
void StgRigid_Launch(s32 id, Vec4 *push, s32 material);

/* Like StgRigid_Launch with a given spin and an upward speed of 5..10. No caller. */
void StgRigid_LaunchSpin(s32 id, Vec4 *push, Vec4 *angVel);

/* Takes a body off the active list and puts its node on the free list. */
void StgRigid_Release(s32 id) {
    StgRigidNode *n = StgRigid_Find(id);

    if (n == NULL) {
        return;
    }
    if (gStgRigid->active == n) {
        gStgRigid->active = n->next;
    } else {
        if (n->prev != NULL) {
            n->prev->next = n->next;
        }
        if (n->next != NULL) {
            n->next->prev = n->prev;
        }
    }
    n->next = gStgRigid->free;
    gStgRigid->free = n;
}

/* One frame of every body: 10 sub-steps of STG_RIGID_DT (until the summed time passes 1 / 6). Nothing while paused. */
void StgRigid_Update(void);

/* Writes a body's world matrix; returns 0 when the id names no body. */
s32 StgRigid_GetMatrix(Mtx44 *out, s32 id);

/* A body's collision sphere, NULL when the id names no body. No caller. */
RigidSphere *StgRigid_GetSphere(s32 id);

/* Makes a box empty (min = +1e10, max = -1e10) so that points can be added to it. First of the box helpers. */
void StgAabb_SetEmpty(StgAabb *box);
