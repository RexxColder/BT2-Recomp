#include "common.h"
#include "battle/battle.h"
#include "battle/btl_demo_cam.h"
#include "sys/heap.h"

/* Scripted (demo) camera, 0x23D1E8-0x23E040. See battle/btl_demo_cam.h. */

extern void *memset(void *dst, s32 c, u32 n);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_SetZeroW1(Vec4 *dst);                /* dst = 0 */
extern void Mtx_StoreIdentity(Mtx44 *dst);
extern void Mtx_Mul(Mtx44 *a, Mtx44 *b, Mtx44 *dst); /* matrix product */
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);       /* copy */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);       /* inverse of a rotation + translation matrix */
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about Z */
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about X */
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about Y */
extern void Vu0View_LoadMtx(Mtx44 *m);

extern void *BtlObj_Get(s32 id);
extern void *BtlCharApi_GetPlayer(void *arg);
extern s32 BtlCharApi_HasMemberUnk70(void *arg);
extern void BtlCharApi_GetCamUnk460(void *arg, Vec4 *out);
extern s32 BtlStage_IsReady(void);
extern DemoCamAnim *BtlStage_GetFileMember(s32 idx);          /* the stage's camera animation idx (0..2) */
extern u8 *BtlObj_GetNode(void *obj, s32 arg);

/* Turns the file offsets of a camera animation into pointers (once). */
void DemoCam_FixupAnim(DemoCamAnim *anim) {
    s32 i;
    DemoCamChannel *ch;

    if (anim->needsFixup != 0) {
        anim->channels = (DemoCamChannel *)((u8 *)anim->channels + (s32)anim);
        anim->defaults = (DemoCamPose *)((u8 *)anim->defaults + (s32)anim);
        if (anim->unk1C != NULL) {
            anim->unk1C = anim->unk1C + (s32)anim;
        }
        if (anim->version < 2) {
            anim->unk1C = NULL;
        }
        ch = anim->channels;
        for (i = 0; i < anim->channelCount; i++) {
            ch->keys = (DemoCamKey *)((u8 *)ch->keys + (s32)anim);
            ch++;
        }
        anim->needsFixup = 0;
    }
}

/* Evaluates the current animation at `time`: defaults, then each channel's keys (linear or step). */
void DemoCam_EvalAnim(DemoCamPose *out, f32 time);

/* Returns the demo camera block. */
DemoCam *DemoCam_Get(void);

/* Forgets the animation and state (everything after the view), back to a full-screen idle camera. */
void DemoCam_Reset(void);

/* Allocates the demo camera. */
void DemoCam_Init(void);

/* Frees the demo camera. */
void DemoCam_Term(void);

/* Selects the animation to play (fixing up its pointers) and detaches the camera from any object. */
void DemoCam_SetAnim(DemoCamAnim *anim);

/* Per frame: advances and evaluates the animation (or the fixed pose), adds shake, builds and applies the view. */
#if 0
/* 11 of 384 instructions differ, all in the fixed-pose branch: the registers holding &pos and &rot are swapped
 * ($s0 / $s1). The animation branch, the frame layout and every call match. (Routing the tail through a shared
 * `Vec4 *eye` fixes that swap but swaps the registers of from/to/hit in the collision part instead.) */
/* Second cleanup pass (allocator dump): both addresses live in one basic block and tie exactly in the local
 * allocator's priority (&pos 5 references over 120 instructions, &rot 4 over 96: 2 * 5 / 120 = 2 * 4 / 96); the
 * original has &pos first, so one instruction more or less at that stage decides it. Tried without effect: the
 * offset additions of rot in front of those of pos (29 differences), `rot.w` / `pos.w` set behind the next
 * call (15, 16). */
s32 DemoCam_Update(void);
#else

#endif

/* Sets the matrix the animation is relative to (ignored while no animation is selected). */
void DemoCam_SetBase(Mtx44 *base);

/* Length of the selected animation (0 without one). */
f32 DemoCam_GetLength(void);

/* Current animation time (0 without an animation). */
f32 DemoCam_GetTime(void);

/* Sets the animation time, remembering the smaller of the old and new one. */
void DemoCam_SetTime(f32 time);

/* 1 while the demo camera owns the screen; a pending stop request resets it and gives 0. */
s32 DemoCam_IsActive(void);

/* 1 when an animation is selected, else whether the fixed pose is on. */
s32 DemoCam_IsInUse(void);

/* Starts the selected animation; the caller steps the time. */
void DemoCam_Start(void);

/* Starts the selected animation, advancing by itself and holding its last frame. */
void DemoCam_StartAuto(void);

/* Starts the selected animation, advancing by itself and ending the demo camera at its end. */
void DemoCam_StartAutoOnce(void);

/* Asks for the animation to end at the next DemoCam_IsActive(). */
void DemoCam_Stop(void);

/* Attaches the animation to an object. */
void DemoCam_SetObj(void *obj);

/* Attaches the animation to a fighter. */
void DemoCam_SetChr(void *chr);

/* Adds a shake of strength 1 lasting `time` seconds. */
void DemoCam_AddShake(f32 time);

/* Time left of the demo camera's shake. */
f32 DemoCam_GetShakeTime(void);

/* Switches to a fixed pose (ending any animation). */
void DemoCam_SetFixedPose(Vec4 *pos, Vec4 *rot);

/* Copies the fixed pose out. */
void DemoCam_GetFixedPose(Vec4 *pos, Vec4 *rot);

/* Enables scaling the animated camera height by the attached fighter's size. */
void DemoCam_SetScaleHeight(s32 on);

/* Leaves the fixed pose. */
void DemoCam_ClearFixed(void);

/* Whether the fixed pose is on. */
s32 DemoCam_IsFixed(void);

/* Plays camera animation `idx` of a battle object (pointer table at obj + 0xB0), attached to it. */
void DemoCam_PlayObjAnim(s32 objId, s32 idx);

/* Plays the fighter's camera animation at obj + 0x908, attached to the fighter. */
void DemoCam_PlayCharAnim0(s32 objId);

/* Plays the fighter's camera animation at obj + 0x90C, attached to the fighter. */
void DemoCam_PlayCharAnim1(s32 objId);

/* Plays the fighter's camera animation at obj + 0x910, attached as an object. */
void DemoCam_PlayCharAnim2(s32 objId);

/* Plays the stage's camera animation idx (the intro cuts) in world space; 0 if the stage has none. */
s32 DemoCam_PlayStageAnim(s32 idx);
