#include "common.h"
#include "main.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "battle/btl_demo_cam.h"
#include "sys/heap.h"
#include "sys/pad.h"

/* Battle camera, 0x23E040-0x23F620. See battle/btl_cam.h for the structures and the per-frame flow. */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);

/* Vector / matrix maths (VU0 macro-mode routines at 0x120098..0x1222xx). */
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec4_SetZeroW1(Vec4 *dst);               /* dst = 0 */
extern void Vec4_SetZero(Vec4 *dst);               /* dst = 0 */
extern f32 Vec3_DistSq(Vec4 *a, Vec4 *b);         /* distance */
extern void Mtx_StoreIdentity(Mtx44 *dst);
extern void Mtx_Mul(Mtx44 *a, Mtx44 *b, Mtx44 *dst); /* matrix product */
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);      /* copy */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);      /* gives the camera axes as rows 0..2 */
extern void Vu0Screen_SetMulMtx(Mtx44 *a, Mtx44 *b);          /* product into VU0 registers ... */
extern void Vu0Screen_StoreMtx(Mtx44 *dst);                /* ... stored here */
extern void Vu0Clip_SetMulMtx(Mtx44 *a, Mtx44 *b);
extern void Vu0Clip_StoreMtx(Mtx44 *dst);
extern void Vu0Screen_LoadMtx(Mtx44 *src);                /* loads the world-to-screen matrix into VU0 registers */
extern void Vu0Clip_LoadMtx(Mtx44 *src);                /* loads the world-to-clip matrix into VU0 registers */
extern void Vu0View_SetRotTrans(Vec4 *rot, Vec4 *trans);  /* rotation + translation matrix into VU0 registers ... */
extern void Vu0View_StoreMtx(Mtx44 *dst);                /* ... stored here */

/* Battle side. */
extern s32 BattleSide_GetObjId(s32 side);                 /* id of the side's fighter object */
extern s32 BattleReplay_IsActive(void);
extern s32 BattleSide_GetControl(s32 side);
extern void BtlCharApi_GetCamPose(s32 objId, Vec4 *pos, Vec4 *rot); /* the fighter camera's pose */
extern s32 BtlCharApi_HasCamPriority(s32 objId);                /* the fighter camera's priority */
extern s32 BtlCharApi_GetMgrUnk134(void);
extern s32 StgCol_TraceSphere(s32 obj, void *seg, Vec4 *hitPos, f32 *frac, void *unk);
extern s32 BtlStage_FindZoneNear(s32 arg0, Vec4 *pos);
extern s32 D_002FF280[2];

extern View gDbgCamView;
extern s32 gDbgCamLocked;

/* Rebuilds the projection matrices of a view from its parameters. */
void View_BuildProjection(View *view);

/* Stores the projection parameters (the larger aspect factor becomes 1) and rebuilds the projection. */
void View_SetProjection(View *view, Vec4 *screenSize, f32 screenDist, f32 aspectX, f32 aspectY, f32 centerX,
                        f32 centerY, f32 zMin, f32 zMax, f32 nearZ, f32 farZ, f32 unk258);

/* Combines the projections with the view matrix, records the camera position and makes the view current. */
void View_UpdateMatrices(View *view, Vec4 *pos);

/* Builds the world-to-view matrix of a camera at pos with rotation rot into both destinations. */
void View_SetTransform(Mtx44 *dst0, Mtx44 *dst1, Vec4 *pos, Vec4 *rot);

/* Loads the view's combined matrices for drawing, optionally sets its scissor, and makes it current. */
void View_Apply(View *view, s32 scissor);

/* Horizontal (XZ) distance from pos to the current view's camera. */
f32 View_GetDistXZ(Vec4 *pos);

/* Gives a view the projection and scissor of a screen layout (full, left half, right half). */
void View_InitLayout(View *view, s32 layout);

/* Copies a layout template over a battle view and records whether it is a half-screen one. */
void BtlCam_SetViewLayout(BtlCamView *view, s32 layout);

/* Builds the three layout templates and gives the two battle views their layout for the screen mode. */
void BtlCam_InitViews(void);

/* Turns a battle view's pose into its matrices and optionally loads them for drawing. */
void BtlCam_BuildView(BtlCamView *view, s32 apply);

/* Clears the camera block, rebuilds the views, selects view 0 and resets the demo camera. */
void BtlCam_Reset(void);

/* Allocates the camera block and the demo camera, and initialises the battle views. */
void BtlCam_Init(void);

/* Frees the camera block and the demo camera. */
void BtlCam_Term(void);

/* Per frame: copies one side's fighter camera pose and priority into the selected view and builds it. */
void BtlCam_UpdateView(s32 side);

/* Segment test from `to` towards `from` against the stage collision: where a camera may stand. */
s32 BtlCam_TraceStage(Vec4 *out, Vec4 *from, Vec4 *to, f32 *frac, s32 *hitObj);

/* Which view to show full screen when neither camera asks for it. */
s32 BtlCam_GetDefaultView(void);

/* Split-screen only: switches the selected view between its half (1) and the full screen (0), rebuilding it. */
void BtlCam_SetLayout(s32 split, s32 apply);

/* The view whose camera has the higher priority; on a tie the default view if the priority is > 0, else -1. */
s32 BtlCam_GetPriorityView(void);

/* Makes one of the two battle views the selected and current one. */
void BtlCam_SelectView(s32 idx);

/* Loads the selected view's matrices (and scissor) for drawing. */
void BtlCam_ApplyView(s32 scissor);

/* Decides whether one full-screen view replaces the per-player views this frame; returns 1 if so. */
s32 BtlCam_UpdateOverride(void);

/* Clears the debug camera's own view and gives it the full-screen layout. */
void DbgCam_Init(void);

/* Free-fly camera: the pad's sticks pan (L1 held) or turn and dolly the pose, then the view is built and applied. */
void DbgCam_Update(View *view, Vec4 *pos, Vec4 *rot, s32 pad, f32 speed);

/* Non-zero makes DbgCam_Update ignore the pad. */
void DbgCam_SetLocked(s32 locked);

/* Registers a shake request in the first slot it dominates, unless a slot already dominates it. */
void CamShake_Add(CamShake *shake, f32 strength, f32 time);

/* Counts every shake slot down by one frame (1/30 s) and clears the expired ones. */
void CamShake_Tick(CamShake *shake) {
    s32 i;

    for (i = 0; i < 4; i++) {
        shake->time[i] -= 0.033333333f;
        if (shake->time[i] < 0.0f) {
            shake->time[i] = 0.0f;
            shake->strength[i] = 0.0f;
        }
    }
}

/* Produces this frame's random position and rotation offsets from the strongest shake slot. */
void CamShake_Calc(CamShake *shake, Vec4 *posOfs, Vec4 *rotOfs);

/* Time left of the strongest shake slot (0 when none is active). */
f32 CamShake_GetTime(CamShake *shake);
