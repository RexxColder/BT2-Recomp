#include "common.h"
#include "battle/btl_char_status.h"

/*
 * Fighter animation control, 0x1C3CA8..0x1C4BF8. See battle/btl_char_status.h for the structures.
 *
 * The fighter keeps the ids (fighter + 0x974: current, requested, previous, second layer); the frame counter
 * itself lives in the fighter's battle object (object + 0xB40). An id indexes the roster table gBtlChars + 0x20
 * (0x19E words of per-animation flags).
 *
 * The action code never starts an animation directly while it runs: it calls BtlAnim_Request (flag 0x2D,
 * 85 call sites) and the request is carried out by BtlAnim_FlushRequest from 0x1E23D0, or it calls
 * BtlAnim_Play (133 call sites) for an immediate change. Starting an animation raises the one-frame flag 0x2B.
 * Each action handler then advances its animation once a frame with BtlAnim_Advance (stops at the end and
 * holds flag 0x31), BtlAnim_AdvanceThen (requests a follow-up animation at the end) or BtlAnim_AdvanceLoop
 * (wraps to frame 0), and times its events with the BtlAnim_Passed... / BtlAnim_In...Range tests, which compare
 * the frame before and after the last advance.
 */

extern BtlStatObj *BtlChar_GetObj(BtlStatChr *chr);
extern s32 BtlChar_TestFlag(BtlStatChr *chr, s32 flag);
extern void BtlChar_SetFlag(BtlStatChr *chr, s32 flag);
extern void BtlChar_SetHeldFlag(BtlStatChr *chr, s32 flag);
extern void BtlChar_ClearFlag(BtlStatChr *chr, s32 flag);
extern s32 BtlChar_TestPrevFlag(BtlStatChr *chr, s32 flag);              /* the flag in the second pair of flag arrays */
extern void BtlChar_ClearFlagRange(BtlStatChr *chr, s32 first, s32 last);  /* BtlChar_ClearFlag for first..last */
extern s32 BtlOpp_GetObj(BtlStatChr *chr);                        /* the opponent's battle object (inferred) */
extern s32 BtlCharApi_IsInRushSequence(s32 objId);
extern void BtlObj_SetSubState(BtlStatObj *obj, s32 state, s32 arg);
extern void BtlObjAnim_StartBlend(BtlStatObj *obj, f32 blend);            /* starts a blend of `blend` seconds */
extern void BtlObjAnim_ZeroRootAxes(void *handle, s32 a, s32 b, s32 c);
extern void BtlObjAnim_RebaseRoot(void *handle);
extern void BtlObjAnim_ClearNodeRot(void *handle, s32 node);
extern void BtlObjAnim_Play(BtlStatObj *obj, s32 layer, s32 anim, s32 reset);
extern void BtlObjAnim_PlayFrom(BtlStatObj *obj, s32 other, s32 anim, s32 arg);
extern void BtlObjAnim_PromoteLayer(BtlStatObj *obj);                       /* the second layer becomes the main one */
extern s32 BtlObjAnim_TestEvent(BtlStatObj *obj, u64 mask);              /* attribute test at the current frame */
extern void BtlObj_SetEyeFrame(BtlStatObj *obj, s32 state);
extern s32 BtlObj_GetMouthMode(BtlStatObj *obj);

extern BtlStatRoster *gBtlChars;

/* Applies an animation's table flags 0x40000000 / 0x80000000 / 2 to a layer handle. */
void BtlAnim_ApplyTableFlags(void *handle, s32 anim);

/* Switches off the nodes that models 0x78, 0x98 and 0x99 do not animate. */
void BtlAnim_HideModelNodes(void *handle, s32 model);

/* Switches off node 0x10 of model 0x78. */
void BtlAnim_HideModelNode10(void *handle, s32 model);

/* Starts an animation on the main layer now, raising flag 0x2B; blend > 0 blends into it over that many seconds. */
void BtlAnim_Play(BtlStatChr *chr, s32 anim, f32 blend);

/* Starts an animation on the main layer without resetting the object's state, raising flag 0x2C. */
void BtlAnim_PlayKeep(BtlStatChr *chr, s32 anim, f32 blend);

/* Makes the second layer's animation the main one, raising flag 0x2B. */
void BtlAnim_SubToMain(BtlStatChr *chr);

/* Requests an animation: BtlAnim_FlushRequest starts it with BtlAnim_Play. */
void BtlAnim_Request(BtlStatChr *chr, s32 anim, f32 blend);

/* Requests an animation: BtlAnim_FlushRequestKeep starts it with BtlAnim_PlayKeep. */
void BtlAnim_RequestKeep(BtlStatChr *chr, s32 anim, f32 blend);

/* Requests BtlAnim_SubToMain. */
void BtlAnim_RequestSubToMain(BtlStatChr *chr);

/* Stores the blend time for the next animation start and holds flag 0x32. */
void BtlAnim_SetBlend(BtlStatChr *chr, f32 blend);

/* The same with a blend time of 0. No caller. */
void BtlAnim_SetNoBlend(BtlStatChr *chr) {
    BtlAnim_SetBlend(chr, 0.0f);
}

/* Starts the animation requested with BtlAnim_Request. */
void BtlAnim_FlushRequest(BtlStatChr *chr);

/* Starts the animation requested with BtlAnim_RequestKeep. */
void BtlAnim_FlushRequestKeep(BtlStatChr *chr);

/* Carries out BtlAnim_RequestSubToMain when the second layer has an animation. */
void BtlAnim_FlushSubToMain(BtlStatChr *chr);

/* Hands the stored blend time to the object (0 with flag 0x37) and takes one step off the blend counter. */
void BtlAnim_ApplyBlend(BtlStatChr *chr);

/* Starts an animation on the second layer unless it is already there. */
void BtlAnim_PlaySub(BtlStatChr *chr, s32 anim);

/* Sets object + 0xC8C. */
void BtlAnim_SetUnkC8C(BtlStatChr *chr, f32 v);

/* Sets the frames added per advance. */
void BtlAnim_SetStep(BtlStatChr *chr, f32 step);

/* Sets the step so that the whole animation takes `seconds` (one advance if shorter than a frame). */
void BtlAnim_SetDuration(BtlStatChr *chr, f32 seconds);

/* Sets object + 0xCB8 (1.0 from the manager every frame). */
void BtlAnim_SetObjRate(BtlStatChr *chr, f32 rate);

/* Sets fighter + 0x988 (1.0 from the manager every frame). */
void BtlAnim_SetRate(BtlStatChr *chr, f32 rate);

/* Puts the animation on its last frame, with no blend, and holds the end flag 0x31. */
void BtlAnim_JumpToEnd(BtlStatChr *chr);

/* BtlObjAnim_ZeroRootAxes(main handle, 1, 1, 1): what table flag 0x40000000 does at an animation start. */
void BtlAnim_EnableHandle(BtlStatChr *chr);

/* Current animation id. */
s32 BtlAnim_GetId(BtlStatChr *chr);

/* Requested animation id (-1 after a start). */
s32 BtlAnim_GetNextId(BtlStatChr *chr);

/* Last frame's animation id. */
s32 BtlAnim_GetPrevId(BtlStatChr *chr);

/* Flag word of an animation id from the roster table; 0 when out of range. */
u32 BtlAnim_GetFlags(u32 anim);

/* Current frame. */
f32 BtlAnim_GetFrame(BtlStatChr *chr);

/* Current frame / length, 0..1. */
f32 BtlAnim_GetProgress(BtlStatChr *chr);

/* Length of the current animation in frames. */
f32 BtlAnim_GetLength(BtlStatChr *chr);

/* Frames added per advance. */
f32 BtlAnim_GetStep(BtlStatChr *chr);

/* Object + 0xCB8. */
f32 BtlAnim_GetObjRate(BtlStatChr *chr);

/* Attribute test of the current animation frame; 0 while the frame did not move on the advance before last. */
s32 BtlAnim_TestAttr(BtlStatChr *chr, u64 mask);

/* Advances the animation one step (flags & 1: not while blending); at the end clamps, holds flag 0x31 and returns 1. */
s32 BtlAnim_Advance(BtlStatChr *chr, s32 flags);

/* BtlAnim_Advance, and at the end requests the animation `next`. */
s32 BtlAnim_AdvanceThen(BtlStatChr *chr, s32 next, f32 blend, s32 flags);

/* Advances a looping animation one step (flags & 1: not while blending); at the end goes back to frame 0. */
void BtlAnim_AdvanceLoop(BtlStatChr *chr, s32 flags);

/* 1 when the last advance passed the point `ratio` (0..1) of the animation, wrap-around included. */
s32 BtlAnim_PassedRatio(BtlStatChr *chr, f32 ratio);

/* 1 when the last advance passed frame `frame`, wrap-around included. */
s32 BtlAnim_PassedFrame(BtlStatChr *chr, f32 frame);

/* BtlAnim_InFrameRange with the bounds given as ratios of the length. No caller. */
s32 BtlAnim_InRatioRange(BtlStatChr *chr, f32 lo, f32 hi);

/* 1 when the frames covered by the last advance overlap lo..hi, wrap-around included. */
s32 BtlAnim_InFrameRange(BtlStatChr *chr, f32 lo, f32 hi);

/* 1 on the frame an animation was started (flag 0x2B). */
s32 BtlAnim_IsNew(BtlStatChr *chr);

/* Flag 0x2B in the second pair of flag arrays (the frame before, inferred). */
s32 BtlAnim_WasNew(BtlStatChr *chr);
