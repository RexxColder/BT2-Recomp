#include "common.h"
#include "battle/btl_char_member.h"

/*
 * The one-frame effect request bits of a fighter and everything that reads them: 0x1CF578..0x1D1EC8.
 *
 * One translation unit in the original, from the request-bit helpers (which the member code's header describes)
 * through the effect requests: BtlFx_UpdateGroundFx only compiles to the original bytes when BtlChar_IsFxBitNew is
 * defined earlier in the same file. Where the object really starts is not known (0x1CF578 is the latest place; the
 * read-only data is continuous from the member code). It ends at BtlFx_FireKiBlast only because that function
 * is left in assembly and owns the float constants that follow; btl_char_fx_c.c continues it.
 *
 * The first part (to 0x1D00D8) was written against the member code's view of the fighter (BtlMemberChr), the rest
 * against the effect code's (FxChr). Both views are kept; functions declared with the first view are reached from
 * the second half through cast macros.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 BtlUtil_Clamp(s32 v, s32 lo, s32 hi);
extern s32 BtlUtil_Min(s32 a, s32 b);
extern s32 BtlUtil_Max(s32 a, s32 b);
extern f32 BtlUtil_WrapAngle(f32 a);
extern s32 BtlChar_GetCount(void);
extern BtlMemberChr *BtlChar_Get(s32 i);
extern BtlMemberObj *BtlChar_GetObj(BtlMemberChr *chr);
extern BtlMemberPose *BtlChar_GetPos(BtlMemberChr *chr);
extern s32 BtlChar_IsFrozen(BtlMemberChr *chr);
extern s32 BtlChar_FrameMod(s32 n);
extern void BtlChar_Vibrate(BtlMemberChr *chr, f32 power, f32 seconds);
extern s32 BtlChar_TestFlag(BtlMemberChr *chr, s32 bit);
extern void BtlChar_ClearFlag(BtlMemberChr *chr, s32 bit);
extern void BtlEvent_Raise(s32 side, s32 ev);
extern s32 Battle_GetMode(void);
extern f32 BtlCharApi_GetChargedUnkC78(s32 objId);
extern f32 Mathf_Sin(f32 angle);
extern f32 Mathf_Cos(f32 angle);
extern s32 BtlAnim_GetId(BtlMemberChr *chr);
extern s32 BtlAnim_GetFlags(s32 state);
extern f32 BtlAnim_GetFrame(BtlMemberChr *chr);
extern s32 BtlAnim_TestAttr(BtlMemberChr *chr, u64 mask);
extern f32 BtlStat_GetScale7(BtlMemberChr *chr);
extern s32 BtlOpp_GetPlayer(BtlMemberChr *chr);
extern s32 BtlOpp_HasAbility(BtlMemberChr *chr, s32 n);
extern f32 BtlParam_GetDamageTakenScale(BtlMemberChr *chr);
extern s32 BtlCharApi_IsInTechnique(s32 objId);
extern s32 BtlCharApi_IsInRushSequence(s32 objId);

extern f32 BtlSkill_GetShotUnk30(BtlMemberChr *chr, s32 kind);
extern f32 BtlSkill_GetShotTime(BtlMemberChr *chr, s32 kind);
extern f32 BtlSkill_GetShotSpeed(BtlMemberChr *chr, s32 kind);
extern f32 BtlSkill_GetShotTurnRate(BtlMemberChr *chr, s32 kind);
extern f32 BtlSuper_GetShotUnk6C(BtlMemberChr *chr, s32 kind);
extern f32 BtlSuper_GetShotTime(BtlMemberChr *chr, s32 kind);
extern f32 BtlSuper_GetShotSpeed(BtlMemberChr *chr, s32 kind);
extern f32 BtlSuper_GetShotTurnRate(BtlMemberChr *chr, s32 kind);
extern void EftShot_Request(BtlMemberAuraReq *req);
extern void EftTransform_Start(BtlMemberFx0Req *req);
extern void EftTransform_Flash(void);
extern void EftTransform_End(void);
extern s32 BtlAtk_GetHitFxKind(BtlMemberChr *chr);
extern s32 BtlAtk_GetHitSoundLevel(BtlMemberChr *chr);
extern s32 BtlCharApi_HasWeaponOut(s32 objId);
extern s32 BtlAtk_GetFlags(BtlMemberChr *chr);
extern f32 BtlAtk_GetLaunchAngleA(BtlMemberChr *chr);
extern f32 BtlAtk_GetLaunchAngleB(BtlMemberChr *chr);
extern void BtlOpp_GetTargetPos(BtlMemberChr *chr, Vec4 *out);
extern f32 BtlOpp_GetRadius(BtlMemberChr *chr);
extern void EftImpact_SpawnHit(BtlMemberHitFxReq *req);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern u32 BtlObjAnim_QueryEvent(BtlMemberObj *obj, u64 a, s32 b, s32 c);
extern s32 BtlObjAnim_MaskToNode(u32 mask);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern void BtlCharSnd_PlayCommon(BtlMemberChr *chr, s32 line);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);

extern BtlMemberRoster *gBtlChars;

/* Sets a one-frame effect request bit. */
void BtlChar_SetFxBit(BtlMemberChr *chr, s32 n);

/* Clears a one-frame effect request bit. */
void BtlChar_ClearFxBit(BtlMemberChr *chr, s32 n);

/* Tests an effect request bit of this frame. */
s32 BtlChar_TestFxBit(BtlMemberChr *chr, s32 n);

/* Tests an effect request bit of the frame before. */
s32 BtlChar_TestPrevFxBit(BtlMemberChr *chr, s32 n);

/* Whether the bit is set now and was not last frame. */
s32 BtlChar_IsFxBitNew(BtlMemberChr *chr, s32 n);

/* Whether the bit was set last frame and is not now. */
s32 BtlChar_IsFxBitEnded(BtlMemberChr *chr, s32 n);

/* Returns the sound line for a hit of the given kind, or -1. */
s32 BtlChar_GetHitSoundLine(s32 kind) {
    switch (kind) {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        return BtlChar_FrameMod(2);
    case 5:
    case 9:
    case 10:
    case 11:
    case 12:
        return BtlChar_FrameMod(3) + 6;
    case 6:
        return 0x28;
    case 7:
        return 0x29;
    case 8:
        return 0x2A;
    }
    return -1;
}

/* Spawns the effect requested by fx bits 0x3C..0x40 (the highest set bit picks the kind 0..4). */
void BtlChar_SpawnFxBits3C(BtlMemberChr *chr);

/* Spawns the effects requested by fx bits 0..2, by the kind in chr->unk12DC. */
void BtlChar_SpawnFxBits0(BtlMemberChr *chr);

/* Spawns the hit effect and plays the hit sound requested by fx bits 0x1B..0x27. */
void BtlChar_SpawnHitFx(BtlMemberChr *chr);

/* ------------------------------------------------------------------------------------------------------------
 * Effect requests (0x1D00D8..), written against the effect code's view of the fighter.
 * ------------------------------------------------------------------------------------------------------------ */
#include "battle/btl_char_fx.h"

/*
 * Fighter effect requests, part 1: 0x1D00D8..0x1D0B60.
 *
 * Each function here looks at the one-frame request bits of a fighter (fighter + 0x1262, set by the action code
 * through BtlChar_SetFxBit; last frame's copy at + 0x126B) and starts, keeps or stops one effect of the effect scene.
 * They are called in a fixed order from BtlFx_UpdateAll (btl_char_fx_c.c). Nothing here draws a random number.
 *
 * This file and btl_char_fx_c.c are one run of code, cut after BtlFx_FireKiBlast (0x1D1958). Every function is C;
 * the file's float constants are 0x2FD1D8..0x2FD214 (the last five, 0x2FD200.., are BtlFx_FireKiBlast's).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 atan2f(f32 y, f32 x);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Length(Vec4 *v);
extern f32 BtlUtil_WrapAngle(f32 a);
#define BtlChar_GetObj ((FxObj *(*)(FxChr *chr))BtlChar_GetObj)
#define BtlChar_GetPos ((FxPose *(*)(FxChr *chr))BtlChar_GetPos)
extern s32 BtlChar_TestMemberUnk70(FxChr *chr);
#define BtlMember_GetActiveGauge ((FxGauge *(*)(FxChr *chr))BtlMember_GetActiveGauge)
#define BtlMember_HasAnyListedAbility ((s32 (*)(FxChr *chr))BtlMember_HasAnyListedAbility)
#define BtlChar_TestFxBit ((s32 (*)(FxChr *chr, s32 bit))BtlChar_TestFxBit)           /* test */
#define BtlChar_IsFxBitNew ((s32 (*)(FxChr *chr, s32 bit))BtlChar_IsFxBitNew)           /* set now, clear last frame */
#define BtlChar_IsFxBitEnded ((s32 (*)(FxChr *chr, s32 bit))BtlChar_IsFxBitEnded)           /* clear now, set last frame */
extern void BtlCharApi_GetNodePos(s32 objId, s32 part, Vec4 *out); /* world position of a model part */
#define BtlCharSnd_PlayCommon ((void (*)(FxChr *chr, s32 sound))BtlCharSnd_PlayCommon)
extern void BtlOpp_GetDelta(FxChr *chr, Vec4 *out);
extern s32 BtlParam_GetFlags(FxChr *chr);
extern void BtlParam_GetUnk0(FxChr *chr);
extern s32 BtlKiBlast_GetType(FxChr *chr);
extern s32 BtlKiBlast_GetUnk3(FxChr *chr);
extern void BtlObj_SetColorMode(FxObj *obj, s32 bit, s32 on);
extern s32 BtlObj_GetNodeSide(s32 kind);
extern void EftSpdLine_SpawnBodyTrails(s32 objId);
extern void EftAura_SetLevel(s32 objId, f32 level);
extern void EftAura_Command(s32 objId, s32 cmd);
extern void EftDisc_SpawnHeld(FxHitArg *arg, s32 kind);
extern void EftGlow_Request(s32 player, s32 cmd);
extern s32 EftCharge_IsActive(s32 objId);
extern void EftCharge_Start(s32 *arg);
extern void EftCharge_Burst(s32 objId);
extern void EftCharge_Stop(s32 objId);
extern void EftBlastCharge_Start(FxHitArg *arg);
extern void EftRay_CreateByValue(FxLineArg *arg);
extern void EftShotFx_Start(s32 objId, s32 kind);
#define EftImpact_SpawnHit ((void (*)(FxPosArg *arg))EftImpact_SpawnHit)
extern void EftShock_Start(s32 *arg);
extern void StgBlur_SetPasses(s32 view, s32 mode);
extern void StgBlur_SetCenter(s32 view, Vec4 *pos, s32 arg);
extern void StgBlur_SetColor0Rgba(s32 view, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor1Rgba(s32 view, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor2Rgba(s32 view, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor3Rgba(s32 view, s32 r, s32 g, s32 b, s32 a);

/* Request 0x20: effect 0xE between model part 0x2E and the fighter, with sound 0x46. */
void BtlFx_SpawnFlashReq20(FxChr *chr);

/* Request 0x2B: effect 0xD at model part 0x10. */
void BtlFx_SpawnFlashReq2B(FxChr *chr);

/* Request 0x17: the hit spark at the recorded hit position, by the attack's class. */
void BtlFx_SpawnHitSparkReq17(FxChr *chr);

/*
 * The aura: level = ki ratio when at least half full (1 with object flag 0x40000 or request 0x13, 0 with request 0x14
 * or when the action has attribute 0x10 without one of the listed abilities); requests 7 / 8 send its commands 2..4.
 * Not void in the original: the last call is not a tail call.
 */
s32 BtlFx_UpdateAura(FxChr *chr);

/* Requests 7 and 8: keeps effect 0x1762A8 alive while 7 is set; 8 triggers its burst. */
void BtlFx_UpdateChargeFx(FxChr *chr);

/* Requests 4 and 5: the powered-up look (object mask bit 6) and its aura variant. Not void in the original (no tail call). */
s32 BtlFx_UpdatePowerUpLook(FxChr *chr);

/* Request 6: effect 0x1A6FD0. */
void BtlFx_SpawnReq6(FxChr *chr);

/*
 * Requests 9 and 10: fades the view's screen filter in (1/6 per frame) and out (1/3 per frame).
 * The compiler truncates decimal literals, so the two steps are written one digit up to give the original bits
 * (0x3E2AAAAB and 0x3EAAAAAB, the values rounded to nearest).
 */
void BtlFx_UpdateScreenFilter(FxChr *chr);

/* Requests 0xC..0xF: one-shot effects 0..3 of module 0x180A00. */
void BtlFx_SpawnBurstReqC(FxChr *chr);

/* Request 0xB: effect 0x15EF18 while moving faster than half the reference speed. */
void BtlFx_SpawnFastMoveFx(FxChr *chr);

/* Request 0x15: speed lines; two parameters follow the direction to the opponent relative to the camera yaw and the distance. */
/*
 * Matching notes: the defaults are an aggregate initialiser (the compiler builds it in a stack temporary, clearing
 * the vector with memset, and copies it; the temporary's slot is then reused for the direction vector). The
 * colour has to be a scalar followed by an array of three (see FxLineArg) and the 0.001 a variable assigned
 * before `angle`, or the stores and the constant loads are scheduled differently.
 */
void BtlFx_SpawnSpeedLines(FxChr *chr);

/*
 * Fighter effect requests, part 2: 0x1D0B60..0x1D1EC8 (formerly btl_char_fx_b.c).
 * More request-bit readers (ground, water, clash), the object flags that follow fighter state, and the hit sparks
 * spawned by animation event 4. BtlFx_FireKiBlast is the only function of the effect files that draws random
 * numbers (BtlChar_RandF, the fighters' own generator).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Mathf_Sin(f32 a);
extern f32 Mathf_Cos(f32 a);
extern f32 BtlUtil_WrapAngle(f32 a);
#define BtlChar_GetObj ((FxObj *(*)(FxChr *chr))BtlChar_GetObj)
#define BtlChar_GetPos ((FxPose *(*)(FxChr *chr))BtlChar_GetPos)
#define BtlChar_TestFlag ((s32 (*)(FxChr *chr, s32 flag))BtlChar_TestFlag)
extern s32 BtlChar_TestMemberUnk70(FxChr *chr);
#define BtlChar_SetFxBit ((void (*)(FxChr *chr, s32 bit))BtlChar_SetFxBit)          /* set */
#define BtlChar_ClearFxBit ((void (*)(FxChr *chr, s32 bit))BtlChar_ClearFxBit)          /* clear */
#define BtlChar_TestFxBit ((s32 (*)(FxChr *chr, s32 bit))BtlChar_TestFxBit)           /* test */
#define BtlChar_IsFxBitNew ((s32 (*)(FxChr *chr, s32 bit))BtlChar_IsFxBitNew)           /* set now, clear last frame */
#define BtlChar_IsFxBitEnded ((s32 (*)(FxChr *chr, s32 bit))BtlChar_IsFxBitEnded)           /* clear now, set last frame */
extern void BtlCharApi_GetNodePos(s32 objId, s32 part, Vec4 *out); /* world position of a model part */
#define BtlCharSnd_PlayCommon ((void (*)(FxChr *chr, s32 sound))BtlCharSnd_PlayCommon)
extern s32 BtlChar_TestPrevFlag(FxChr *chr, s32 flag);            /* fighter flag, last frame */
extern s32 BtlParam_GetFlags(FxChr *chr);
extern f32 BtlAtk_GetLaunchAngleAOf(FxChr *chr, s32 param);
extern f32 BtlAtk_GetLaunchAngleBOf(FxChr *chr, s32 param);
extern s32 BtlKiBlast_GetType(FxChr *chr);
extern s32 BtlKiBlast_GetUnk3(FxChr *chr);
extern s32 BtlStage_GetWaterLevel(f32 *height);
extern s32 BtlObj_GetNodeSide(s32 kind);
extern void EftBubble_StartBurst(s32 objId);
extern void EftWater_SetWake(s32 objId, s32 off);
extern void EftWater_AddSplashFor(s32 objId, Vec4 *pos, s32 arg, f32 speed);
extern void EftAbsorb_Start(FxArg2 *arg);
extern void EftAbsorb_Stop(s32 objId);
extern void EftAbsorb_StartHands(FxArg2 *arg);
extern void EftBodyFx_Start(FxArg3 *arg);
extern void EftBodyFx_Stop(s32 objId);
extern void EftRushBurst_Start(FxDirArg *arg);
extern void EftRushBurst_Stage2(s32 objId);
extern void EftRushBurst_Stop(s32 objId);
extern void EftRay_StartHit(s32 objId, Vec4 *pos, s32 a, s32 b, s32 c, f32 scale);
#define EftImpact_SpawnHit ((void (*)(FxPosArg *arg))EftImpact_SpawnHit)
extern void EftGndDust_SetSlide(s32 objId, s32 off, f32 scale);
extern void EftGndDust_SetDash(s32 objId, s32 off, f32 scale);
extern void EftGndDust_SpawnBurst(s32 objId, f32 a, f32 b);
extern void EftGndDust_SpawnLanding(s32 objId, Vec4 *pos, Vec4 *normal, f32 scale);
extern void EftGndDust_Stub(s32 objId, f32 scale);
extern void EftGndDust_SpawnImpact(s32 objId, Vec4 *pos, f32 scale);
extern void EftCharaFx_Start(FxArg2 *arg);
extern void EftCharaFx_Stop(s32 objId);
extern void EftImpact_SpawnHitScaled(FxPosArg *arg, f32 size);
extern void Vec4_Lerp(Vec4 *out, Vec4 *a, Vec4 *b, f32 t);
extern s32 BtlOpp_GetObjId(FxChr *chr);
extern s32 BtlCharApi_IsModelNew(s32 objId);
#define BtlMember_GetActive ((s32 *(*)(FxChr *chr))BtlMember_GetActive)
#define BtlMember_HasAbility ((s32 (*)(FxChr *chr, s32 param))BtlMember_HasAbility)
extern void BtlCharApi_ShakeCamsNear(Vec4 *pos, f32 near, f32 far, f32 strength, f32 time);
extern void BtlObjFlash_Start(FxObj *obj, s32 kind);
extern void BtlObj_SetEyeFrame(FxObj *obj, s32 arg);
extern s32 BtlObj_GetMouthMode(FxObj *obj);
extern s32 BtlObj_GetEyeFrame(FxObj *obj);
extern void BtlObj_SetSubState(FxObj *obj, s32 state, s32 arg);
#define BtlAnim_TestAttr ((s32 (*)(FxChr *chr, u64 mask))BtlAnim_TestAttr)           /* animation event bits raised this frame */
extern f32 BtlOpp_GetDistance(FxChr *chr);
extern void BtlChar_ToggleHeldFlag(FxChr *chr, s32 flag);
extern f32 BtlAct_GetHeight(FxChr *chr);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlKiBlast_GetCurrentKind(FxChr *chr);
extern s32 BtlKiBlast_GetFlags(FxChr *chr);
extern f32 BtlKiBlast_GetSpeed(FxChr *chr);
extern f32 BtlKiBlast_GetTurnRate(FxChr *chr);
extern s32 BtlKiBlast_GetFrames(FxChr *chr);
extern s32 BtlKiBlast_GetUnk31(FxChr *chr);
extern s32 BtlKiBlast_GetHits(FxChr *chr);
extern f32 BtlKiBlast_GetUnk28(FxChr *chr);
extern f32 BtlKiBlast_GetUnk2C(FxChr *chr);
extern s32 BtlObjAnim_GetEventArg(FxObj *obj, u64 mask);
#define BtlObjAnim_MaskToNode ((s32 (*)(s32 bits))BtlObjAnim_MaskToNode)
#define BtlObjAnim_QueryEvent ((s32 (*)(FxObj *obj, u64 a, s32 b, s32 c))BtlObjAnim_QueryEvent)
extern void Vec3_Normalize(Vec4 *out, Vec4 *in);
extern void Vec3_RotateAxis(Vec4 *out, Vec4 *a, Vec4 *b, f32 s);
extern void Vec3_RotateY(Vec4 *out, Vec4 *in, f32 s);
extern void EftDisc_Throw(FxHitArg2 *arg);
extern void EftDisc_SpawnFromNode(FxHitArg2 *arg);
extern void EftKiBlast_Fire(FxHitArg2 *arg);
extern void EftKiBomb_Fire(FxHitArg2 *arg);
extern void EftKiObj_Create(FxHitArg2 *arg);
extern f32 BtlChar_RandF(void);
extern s32 BtlChar_FrameMod(s32 n);
extern void BtlChar_SetSmallVibration(FxChr *chr, f32 seconds);

/* Request 0x18: effect 0x17D500 at model part 0x11. */
void BtlFx_SpawnReq18(FxChr *chr);

/* Requests 0x2F..0x36: ground effects (dust, or splashes when the ground point is under water). */
/*
 * Matches only with BtlChar_IsFxBitNew (0x1CF620) defined earlier in the same translation unit: then the first
 * branch takes "li a1,0x2F" into its delay slot as the original does. Compiled on its own the branch becomes a
 * branch-likely with "move a0,s1". This is the evidence that the request-bit helpers and the effect requests were
 * one source file.
 */
/*
 * The effect calls that take a float go through inline wrappers: without them the compiler keeps a repeated
 * constant in a saved register across the calls, which the original does not.
 */
static inline void Fx_FootDust(s32 objId, Vec4 *pos, f32 scale);

void BtlFx_UpdateGroundFx(FxChr *chr);

/* Water: the splash when flag 0x11 changes, and the wake (request 0x19) while moving fast with flag 0x12. */
void BtlFx_UpdateWaterFx(FxChr *chr);

/* Requests 0x28..0x2A: effect 0x171C78 along a direction from two action parameters, and its two follow-ups. */
void BtlFx_UpdateAimedFxReq28(FxChr *chr);

/* Request 0x1A: effect 0x16B418 while set. */
void BtlFx_UpdateReq1A(FxChr *chr);

/* Request 0x38: effect 0x15EDF0 while set. */
void BtlFx_UpdateReq38(FxChr *chr);

/* Request 0x37: effect 0x15EEC0. */
void BtlFx_SpawnReq37(FxChr *chr);

/* Request 0x2E: effect 0xB between model part 0x11 and the point stored at chr + 0x1360. */
void BtlFx_SpawnFlashReq2E(FxChr *chr);

/* Characters 0x37, 0x98, 0x99: keeps effect 0x1749F0 running while request 0x3A is set, or with flag 0xE out of water. */
void BtlFx_UpdateCharaFx(FxChr *chr);

/* Requests 0x2C / 0x2D: a clash flash halfway to the opponent (size 3 or 6); the big one shakes nearby cameras. */
void BtlFx_SpawnClashFlash(FxChr *chr);

/* Request 0x1D: object trigger 0. */
void BtlFx_TriggerObjReq1D(FxChr *chr);

/* Request 0x1E: object trigger 1, repeated every 4 frames while set. */
void BtlFx_TriggerObjReq1E(FxChr *chr);

/* Request 0x1F: object trigger 2, repeated every 4 frames while set. */
void BtlFx_TriggerObjReq1F(FxChr *chr);

/* Request 3: object flag byte 2 becomes 8 when it starts and 1 when it ends. */
void BtlFx_UpdateObjFlagReq3(FxChr *chr);

/* Object flag 0x2000000 = the camera trace hit something and flag 0x12D is clear. */
void BtlFx_UpdateOccludedFlag(FxChr *chr);

/* Fighter flag 0x137 sends the object command 1; otherwise command 9 once BtlObj_GetEyeFrame answers 1. */
void BtlFx_UpdateObjCmdFlag137(FxChr *chr);

/* Fighter flag 0x96 holds the object in sub-state 5 (from 0 or 4); clearing it returns to 0. */
void BtlFx_UpdateSubStateFlag96(FxChr *chr);

/* Object flag 0x80 follows action parameter 0x79 while the action has attribute 0x200000 (only with flag 2 set). */
void BtlFx_UpdateObjFlag80(FxChr *chr);

/*
 * Animation event 4 (a hit landed on this fighter): one to n sparks at the hit position, the hit sound and a 0.1 s
 * buzz of the small motor. Reaction kind 0 jitters every spark with three BtlChar_RandF draws (x, y, z; +-0.2, or
 * -0.2..0 on y when the fighter is not above three times its body height); kinds 2..6 with flag 5 push the spark
 * sideways (2) or along the hit vector by the opponent distance.
 */
/*
 * Matching notes: every case of the size switch has its own body (the compiler merges the identical ones after
 * register allocation; written with shared bodies the function has fewer instructions in front of the loop, the
 * hit count and `code` then outrank the object pointer and the hoisted constant 2 for a saved register, and the
 * registers come out differently). The two owner stores are in the order objId2, objId.
 */
void BtlFx_FireKiBlast(FxChr *chr);
