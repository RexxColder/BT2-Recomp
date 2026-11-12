#include "common.h"
#include "battle/btl_char_fx.h"

/*
 * Fighter effect requests, part 3: 0x1D1EC8..0x1D3B40.
 * Animation events of the fighter's model (BtlAnim_TestAttr), the per-frame passes the fighter manager calls, the
 * stage effect shared by the roster, and the partner object (a second character model attached to a fighter by the
 * object load job, fighter + 0x1330).
 */

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Mathf_Sin(f32 a);
extern f32 Mathf_Cos(f32 a);
extern f32 BtlUtil_WrapAngle(f32 a);
extern FxObj *BtlChar_GetObj(FxChr *chr);
extern FxPose *BtlChar_GetPos(FxChr *chr);
extern s32 BtlChar_TestFlag(FxChr *chr, s32 flag);
extern void BtlChar_SetFxBit(FxChr *chr, s32 bit);          /* set */
extern s32 BtlChar_TestFxBit(FxChr *chr, s32 bit);           /* test */
extern void BtlCharApi_GetNodePos(s32 objId, s32 part, Vec4 *out); /* world position of a model part */
extern void BtlCharSnd_PlayCommon(FxChr *chr, s32 sound);
extern void BtlObj_SetColorMode(FxObj *obj, s32 bit, s32 on);
extern void EftShotFx_Start(s32 objId, s32 kind);
extern void EftImpact_SpawnHit(FxPosArg *arg);
extern s32 *BtlMember_GetActive(FxChr *chr);
extern void BtlObj_SetEyeFrame(FxObj *obj, s32 arg);
extern s32 BtlObj_GetMouthMode(FxObj *obj);
extern void BtlObj_SetSubState(FxObj *obj, s32 state, s32 arg);
extern s32 BtlAnim_TestAttr(FxChr *chr, u64 mask);           /* animation event bits raised this frame */
extern s32 BtlAnim_GetId(FxChr *chr);                      /* the current animation number */
extern s32 BtlAnim_GetFlags(s32 anim);                        /* its attribute bits */
extern s32 BtlOpp_GetPlayer(FxChr *chr);                      /* the opponent's roster index */
extern s32 BtlAct_GetCurrent(FxChr *chr);
extern s32 BtlAct_IsTechniqueId(s32 action);
extern s32 BtlAct_GetCurrentClass(FxChr *chr);
extern void BtlAct_PushAngle(FxChr *chr, f32 yaw, f32 a, f32 b);
extern s32 BtlCharApi_IsInRushSequence(s32 objId);
extern s32 BtlCharApi_IsInSkill(s32 objId);
extern s32 BtlCharApi_HasWeaponOut(s32 objId);
extern s32 BtlAtk_GetId(FxChr *chr);
extern s32 BtlAtk_GetFlags(FxChr *chr);
extern s32 BtlAtk_GetHitSoundLevel(FxChr *chr);
extern s32 BtlSuper_GetFlagsA(FxChr *chr, s32 slot);
extern s32 BtlSkill_GetId(FxChr *chr, s32 slot);
extern s32 BtlChar_GetHitSoundLine(s32 kind);
extern s32 BtlObjAnim_GetEventArg(FxObj *obj, u64 mask);
extern s32 BtlObjAnim_MaskToNode(s32 bits);
extern s32 BtlObjAnim_QueryEvent(FxObj *obj, u64 a, s32 b, s32 c);
extern void BtlObj_GetNodeVelocity(FxObj *obj, s32 part, Vec4 *out);
extern void Mtx_MulVec4(Vec4 *out, void *mtx, Vec4 *in);
extern void EftSpdLine_SpawnPartStreaks(s32 objId, Vec4 *pos, s32 part);
extern s32 BtlChar_FrameMod(s32 n);
extern void BtlChar_Vibrate(FxChr *chr, f32 power, f32 seconds);
extern void BtlChar_SetHeldFlag(FxChr *chr, s32 flag);
extern void BtlChar_ClearFlag(FxChr *chr, s32 flag);
extern FxChr *BtlChar_Get(s32 i);
extern s32 BtlChar_IsFrozen(FxChr *chr);
extern void BtlChar_PlayVoice(FxChr *chr, s32 kind);
extern void ChrCam_AddShake(FxChr *chr, f32 strength, f32 time);
extern s32 BtlObjAnim_TestEvent(FxObj *obj, u64 mask);
extern void BtlCharSnd_RequestAt(Vec4 *pos, s32 kind, s32 id, f32 near, f32 far);
extern void BtlObjXf_Update(FxObj *obj);
extern void BtlObjAnim_PlayModel(FxObj *obj, s32 anim, s32 arg);
extern void BtlObj_SaveNodePositions(FxObj *obj, s32 arg);
extern void BtlObjAnim_SamplePose(FxObj *obj);
extern void BtlObjAnim_UpdateEvents(FxObj *obj);
extern void BtlObjPose_CalcMatrices(FxObj *obj);
extern void BtlObj_UpdateChains(FxObj *obj);
extern void BtlObj_CopyLipTables(FxObj *obj, FxObj *owner);
extern void BtlObj_AddPush(FxObj *obj, Vec4 *v, f32 arg);
extern void BtlObj_AddSway(FxObj *obj, f32 a, f32 b);
extern void StgTint_Start(s32 a, s32 b, f32 time);
extern void BtlChar_SpawnFxBits3C(FxChr *chr);
extern void BtlChar_SpawnFxBits0(FxChr *chr);
extern void BtlChar_SpawnHitFx(FxChr *chr);
extern s32 BtlChar_TestPrevFxBit(FxChr *chr, s32 bit);
extern s32 BtlChar_GetCount(void);
extern FxObj *BtlObj_Get(s32 id);
extern s32 BtlObj_Destroy(s32 id);
extern void BtlRes_Free(s32 number);
extern void Vec4_Scale(Vec4 *out, Vec4 *in, f32 s);
extern FxSave *gSaveData;

/*
 * Animation events 0x100 / 0x80 (light / heavy impact): flash at the event's model part and camera shake (only while
 * the object is drawn), sound, and voice kind 1 for the fighter that takes the blow (animation flag 0x10 picks which
 * of the two; not when the other has flag 0x13B or the speaker is frozen).
 * `work` is the alternate sound and later the fighter that speaks: only one variable for both gives the original's
 * register assignment (s1 before the flag in s2).
 */
void BtlFx_HandleImpactEvents(FxChr *chr);

/* Animation event 1: raises request 0x1B when the current technique has attribute 0x80000 and the event value is 1. */
void BtlFx_HandleEvent1(FxChr *chr);

/* Animation events 0x2000000 / 0x4000000: set / clear fighter flag 0x30. */
void BtlFx_HandleFlag30Events(FxChr *chr);

/* Animation event 2: the swing sound of the current attack (not with flag 0x91, nor with 0x60 unless 0x5C). */
void BtlFx_PlaySwingSound(FxChr *chr);

/* Animation event 8: effect 0x15F3D8 at each model part named by the event's value bits (19 of them). */
void BtlFx_SpawnPartFxEvent8(FxChr *chr);

/* Animation event 0x1000000: effect 0xC at each model part named by the event's value bits, with sound 0x4B. */
void BtlFx_SpawnPartFlashes(FxChr *chr);

/*
 * Animation event 0x400 in a damage action (not with class attribute 0x1000000): sets flag 0x9F, and while that flag
 * lasts pushes the fighter, and its partner object, backwards (yaw + pi, speed 1, 5). Not void in the original.
 */
s32 BtlFx_PushBackOnEvent400(FxChr *chr);

/* Animation event 0x400 in a technique of class 0x18: sets object mask bit 2. Not void in the original (no tail call). */
s32 BtlFx_SetObjMaskOnEvent400(FxChr *chr);

static inline void Fx_ShakeCam(FxChr *chr, f32 strength);

/* Animation event bit 46: camera shake 3.0 for 0.3 s. */
void BtlFx_ShakeCamOnEvent(FxChr *chr);

static inline void Fx_Vibrate(FxChr *chr, f32 power);

/* Animation event bit 45: pad vibration 1.0 for 0.2 s. */
void BtlFx_VibrateOnEvent(FxChr *chr);

/* Object animation events: bit 42 spawns effect 0 of module 0x180A00; 0x20 / 0x40 and bits 43 / 44 set / clear object flags 0x20 and 0x40. */
void BtlFxObj_HandleFlagEvents(FxObj *obj);

/* Object animation events that are sounds, played at model part 3 (audible from 200 to 1500 units). */
void BtlFxObj_PlayEventSounds(FxObj *obj);

/* Object animation events bits 56..60: face sub-states 9..11, command 2, and "back to sub-state 0, then command 9". */
void BtlFxObj_HandleSubStateEvents(FxObj *obj);

/* Manager pass (action stage): the object events of the fighter's own model. */
void BtlFx_UpdateObjEvents(FxChr *chr);

/* Manager pass (camera stage): every effect request and animation event of the fighter, in a fixed order. */
void BtlFx_UpdateAll(FxChr *chr);

/* Manager pass (stage 10, after hit detection): the requests raised by hits. */
void BtlFx_UpdateAfterHits(FxChr *chr) {
    BtlFx_TriggerObjReq1D(chr);
    BtlFx_HandleEvent1(chr);
    BtlChar_SpawnHitFx(chr);
    BtlFx_SpawnFlashReq20(chr);
    BtlFx_SpawnClashFlash(chr);
}

/* Manager pass (after the effect scene and the fighter camera): requests 0x37 and 0x2E. */
void BtlFx_UpdatePostScene(FxChr *chr);

/* Manager pass (end of frame): the camera-trace object flag. */
void BtlFx_UpdateLate(FxChr *chr);

/* Turns requests 0x10 / 0x11 into request 0x12 (the stage effect of BtlFx_UpdateStageFx), and drops flag 0x12E when 0x11 ends. */
void BtlFx_UpdateStageFxRequest(FxChr *chr);

/* Roster pass: starts the stage effect 0x247AF8 when any fighter raises request 0x12, and ends it when none does. */
void BtlFx_UpdateStageFx(void);

/* Manager step between the roster passes. */
void BtlFx_UpdateRoster(void);

/* Places an object at a position and rotation. */
void BtlFxObj_Place(FxObj *obj, Vec4 *pos, Vec4 *rot);

/*
 * The partner object's animation events: shown / hidden (0x4000000 / 0x2000000), impact flash with the opponent's
 * voice kind 1, the object sounds, and voice lines (sound kind 7, id = base + chara * 100 + line, base 0x8D4E or
 * 0xCC32 with the alternate voices): lines 0x5F..0x62 of the partner's character under fighter flags 0x130 / 0x131,
 * lines 0x57 / 0x59 / 0x5B (+1) of the fighter's character by technique class 2 / 3 / 4. Each line also sets the
 * partner's sub-state 2 to the line number.
 */
void BtlPartner_HandleEvents(FxObj *obj, FxChr *chr);

/* Whether the fighter has a partner object. */
s32 BtlPartner_IsActive(FxChr *chr);

/* Attaches a partner object (resource slot and battle object) unless one is attached already. */
void BtlPartner_Attach(FxChr *chr, s32 res, s32 objId);

/* Destroys the partner object and frees its resource slot. */
void BtlPartner_Release(FxChr *chr);

/* Manager pass (stage 6): puts the partner on the fighter and runs its animation and pose passes. */
void BtlPartner_Update(FxChr *chr);

/* Manager pass (stage 10): the partner's animation events. */
void BtlPartner_UpdateEvents(FxChr *chr);

/* Starts the partner animation that belongs to a fighter animation number (those from 0x19E up). */
void BtlPartner_PlayAnim(FxChr *chr, s32 anim);

/* Advances the partner animation by its step; 1 when it has reached its end (or there is no partner). */
s32 BtlPartner_StepAnim(FxChr *chr);

/* Sets or clears partner object flag 0x10. */
void BtlPartner_SetFlag10(FxChr *chr, s32 on);

/* Links the partner object to the fighter's object (BtlObj_CopyLipTables). */
void BtlPartner_LinkToOwner(FxChr *chr);

/* The partner object. Without one the original falls off the end (the caller gets the 0 left in the result register). */
FxObj *BtlPartner_GetObj(FxChr *chr);

/* Gives the partner a horizontal velocity along a yaw. */
void BtlPartner_PushAngle(FxChr *chr, f32 yaw, f32 speed, f32 arg);

/* Gives the partner a velocity of a given speed along a direction (ignored when the direction is shorter than 0.0001). */
void BtlPartner_PushDir(FxChr *chr, Vec4 *dir, f32 speed, f32 arg);

/* Forwards two floats to BtlObj_AddSway on the partner. */
void BtlPartner_SetObjFloats(FxChr *chr, f32 a, f32 b);

/* Partner object flag 0x80 = on, while its action has attribute 0x200000 (only with flag 2 set). */
void BtlPartner_SetFlag80(FxChr *chr, s32 on);
