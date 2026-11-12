#include "common.h"
#include "battle/btl_capi_a.h"

/*
 * Fighter interface, first part: 0x204E78..0x207020. 81 accessors keyed by battle object id (a few by roster
 * index), used by the AI, the effect scene and its modules, the camera, the HUD and the fighter code itself. See
 * include/battle/btl_capi_a.h; the same original file continues in btl_char_api.c at 0x207020.
 *
 * Float pool: this file owns .lit4 0x2FE07C..0x2FE0C8 (20 constants, the first of the original object's pool).
 *
 * Shapes that matter for matching here:
 *   - a getter is `if (x != NULL) { return ...; } return 0;` at every nesting level (the original returns the null
 *     pointer register itself);
 *   - a call followed by `return;` is a tail call, a call at the end of an if / else arm is not: the functions
 *     below that end with `if (obj == NULL) { ...; return; }` are written that way for the one call the original
 *     makes with jal;
 *   - the action-id tests are switches (slti ladders), not range compares.
 *
 * Callees still named by address: BtlObj_GetNode(obj, node) model node or NULL, BtlObj_FindBound(obj, n),
 * BtlObj_GetNodeVelocity(obj, node, out), BtlObj_AddPush(obj, vec, arg), Vec4_SetZeroW1 / Vec4_SetZero zero a vector (the
 * first is used for positions, the second for directions and rotations), Mtx_Copy copies a matrix,
 * Vec3_RotateAxis(out, v, axis, angle) turns v about axis.
 */

extern BtlCapiMgr *gBtlChars;
extern f32 sqrtf(f32 x);

extern s32 BtlChar_GetCount(void);
extern BtlCapiChr *BtlChar_Get(s32 idx);
extern BtlCapiChr *BtlChar_FindByObjId(s32 objId);
extern BtlCapiObj *BtlObj_Get(s32 objId);
extern BtlCapiObj *BtlChar_GetObj(BtlCapiChr *chr);
extern BtlCapiPose *BtlChar_GetPos(BtlCapiChr *chr);
extern s32 BtlChar_TestFlag(BtlCapiChr *chr, s32 flag);
extern s32 BtlChar_IsFrozen(BtlCapiChr *chr);
extern f32 BtlChar_RandF(void);
extern f32 BtlChar_GetSpacing(BtlCapiChr *chr, s32 mode); /* own size + the other fighter's + 30 (40 with flag 0x13) */
extern void *BtlMember_GetActive(BtlCapiChr *chr);
extern s32 BtlOpp_GetObjId(BtlCapiChr *chr);
extern void BtlOpp_GetNodePos(BtlCapiChr *chr, s32 node, Vec4 *out);
extern void BtlOpp_GetDelta(BtlCapiChr *chr, Vec4 *out);
extern s32 BtlAct_GetCurrent(BtlCapiChr *chr);
extern s32 BtlAct_GetPrev(BtlCapiChr *chr);
extern s32 BtlAct_IsTechniqueId(s32 action);          /* action is 0x105..0x132: a technique action */
extern s32 BtlAct_GetCurrentClass(BtlCapiChr *chr);
extern s32 BtlAct_GetMotionLevel(BtlCapiChr *chr, s32 anim);
extern s32 BtlAnim_GetId(BtlCapiChr *chr);
extern s32 BtlAnim_GetFlags(s32 anim);
extern s32 BtlParam_GetFlags(BtlCapiChr *chr);    /* parameter word +0x10 */
extern s32 BtlParam_GetAuraKind(BtlCapiChr *chr); /* parameter byte +3, replaced by abilities 0x4D.. */
extern s32 BtlSuper_GetFlags(BtlCapiChr *chr, s32 slot); /* attribute word of technique `slot` */
extern BtlCapiNode *BtlObj_GetNode(BtlCapiObj *obj, s32 node);
extern BtlCapiPart *BtlObj_FindBound(BtlCapiObj *obj, s32 n);
extern void BtlObj_GetNodeVelocity(BtlCapiObj *obj, s32 node, Vec4 *out);
extern void BtlObj_AddPush(BtlCapiObj *obj, Vec4 *v, f32 arg);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern f32 Vec3_Length(Vec4 *v);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec4_SetZeroW1(Vec4 *dst);
extern void Vec4_SetZero(Vec4 *dst);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Vec3_RotateAxis(Vec4 *out, Vec4 *v, Vec4 *axis, f32 angle);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern f32 Mathf_Sin(f32 angle);
extern f32 Mathf_Cos(f32 angle);
extern f32 BtlUtil_ClampF(f32 v, f32 lo, f32 hi);
extern f32 BtlUtil_LengthXZ(Vec4 *v);
extern void BtlUtil_WrapAngles(Vec4 *dst, Vec4 *src);
extern void Quat_ToEuler(Vec4 *out, Quat *q);
extern void Quat_SetIdentity(Quat *q);

/* Character id of the object (object +0xC), 0 for no object. */
s32 BtlCharApi_GetChara(s32 objId);

/* Height of the character model in world units (object +0xFF4, from the model header); 10 for no object. */
f32 BtlCharApi_GetHeight(s32 objId);

/* Object float +0xFF8 (model header +0x1C); 10 for no object. */
f32 BtlCharApi_GetBodyUnkFF8(s32 objId);

/* Object float +0xFFC (model header +0x20): what a placement adds to a path point's y, so the distance from the
   placed point down to the origin; 5 for no object. */
f32 BtlCharApi_GetCenterHeight(s32 objId);

/* Object float +0x1000 (model header +0x24); 5 for no object. No caller. */
f32 BtlCharApi_GetBodyUnk1000(s32 objId);

/* The 16-bit flag word at +0 of the character's parameter block. */
s32 BtlCharApi_ObjGetParamFlags0(s32 objId);

/* The flag word at +0x10 of the character's parameter block. No caller. */
s32 BtlCharApi_ObjGetParamFlags(s32 objId);

/* Aura type of the character: 3 while object flag 0x40000 is set, else the parameter byte +3 (for a fighter: as
   replaced by its abilities, BtlParam_GetAuraKind). */
s32 BtlCharApi_GetAuraType(s32 objId);

/* Float +0xC8 of the character's parameter block. No caller. */
f32 BtlCharApi_GetParamUnkC8(s32 objId);

/* Costume of the fighter's active member. */
s32 BtlCharApi_GetCostume(s32 objId);

/* Both ki blast functions need three plain early returns (object NULL, table NULL, found): the `return 0` of the
   NULL table then keeps a jump with a barrier in front of the loop, the `return 1` block is moved behind it, and
   cross-jumping turns the entry into a jump to the test at the bottom of the loop. A nested `if (e != NULL)` gives
   the same instructions in another block layout. */
/* Whether one of the character's 13 ki blast records (object +0x924) has type 2. */
s32 BtlCharApi_HasKiBlastType2(s32 objId);

/* Whether one of the character's 13 ki blast records has type 3. */
s32 BtlCharApi_HasKiBlastType3(s32 objId);

/* Whether the object id is a fighter's. No caller. */
s32 BtlCharApi_IsFighter(s32 objId);

/* Object id of fighter `player`, or `player` itself when there is none. No caller. */
s32 BtlCharApi_GetObjIdOfPlayer(s32 player);

/* Player index of the fighter (fighter +0), -1 for a non-fighter. No caller. */
s32 BtlCharApi_GetPlayer(s32 objId);

/* Object id of the fighter's opponent. */
s32 BtlCharApi_GetOpponentObjId(s32 objId) {
    BtlCapiChr *chr = BtlChar_FindByObjId(objId);

    if (chr != NULL) {
        return BtlOpp_GetObjId(chr);
    }
    return 0;
}

/* Object id of the fighter's partner object (fighter +0x1338) while it has one (+0x1330), else objId itself. */
s32 BtlCharApi_GetPartnerObjId(s32 objId);

/* Pointer n (0..4) of the five at +0x9C of fighter `player`'s object. */
s32 BtlCharApi_GetPlayerObjUnk9C(s32 player, u32 n);

/* Technique table (object +0x92C, slots 2..4) of fighter `player`. */
void *BtlCharApi_GetPlayerSuperData(s32 player);

/* Skill table (object +0x930, slots 0..1) of fighter `player`. */
void *BtlCharApi_GetPlayerSkillData(s32 player);

/* Word +0x58 of fighter `player`'s object. No caller. */
s32 BtlCharApi_GetPlayerObjUnk58(s32 player);

/* Position: for a fighter its position plus the display offset (hover bob and shake), else the object's +0x970. */
void BtlCharApi_GetPos(s32 objId, Vec4 *out);

/* Position without the display offset. */
void BtlCharApi_GetBasePos(s32 objId, Vec4 *out);

/* Rotation: the fighter's model rotation, else the object's +0x960. */
void BtlCharApi_GetRot(s32 objId, Vec4 *out);

/* Rotation including the animation: fighter rotation plus root motion rotation, or object rotation plus the Euler
   angles of node 0; wrapped. No caller. */
void BtlCharApi_GetModelRot(s32 objId, Vec4 *out);

/* Heading yaw of a fighter, rotation y of another object. No caller. */
f32 BtlCharApi_GetYaw(s32 objId);

/* Pose +0x30: the fighter's movement over the previous frame (between snapshots 0 and 1). */
void BtlCharApi_GetVelocity(s32 objId, Vec4 *out);

/* Pose +0x40: the fighter's whole movement of the previous frame. */
void BtlCharApi_GetFrameMove(s32 objId, Vec4 *out);

/* Unit direction of travel. */
void BtlCharApi_GetDir(s32 objId, Vec4 *out);

/* Speed along the direction of travel, per frame. */
f32 BtlCharApi_GetSpeed(s32 objId);

/* Vertical speed, positive down. */
f32 BtlCharApi_GetFallSpeed(s32 objId);

/* Height (y) of the ground point below the fighter. */
f32 BtlCharApi_GetGroundY(s32 objId);

/* Distance from the fighter down to the ground below it (y is down). */
f32 BtlCharApi_GetAltitude(s32 objId);

/* World position of a model node (translation of its matrix); the object position when the node does not exist. */
void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);

/* The vector at +0x90 of a model node; the object position when the node does not exist. No caller. */
void BtlCharApi_GetNodeUnk90(s32 objId, s32 node, Vec4 *out);

/* World matrix of a model node, identity when there is none. */
void BtlCharApi_GetNodeMtx(s32 objId, s32 node, Mtx44 *out);

/* The second matrix (+0x50) of a model node, identity when there is none. No caller. */
void BtlCharApi_GetNodeMtx50(s32 objId, s32 node, Mtx44 *out);

/* BtlObj_GetNodeVelocity(obj, node, out) on the object, zero for no object. No caller. */
void BtlCharApi_GetNodeRot(s32 objId, s32 node, Vec4 *out);

/* Rotation quaternion (+0xA0) of a model node, identity when there is none. No caller. */
void BtlCharApi_GetNodeQuat(s32 objId, s32 node, Quat *out);

/* Float +0x5C of what BtlObj_FindBound(obj, n) returns, 1.0 when there is none. */
f32 BtlCharApi_GetPartUnk5C(s32 objId, s32 n);

/* The distance under which the opponent counts as close (flags 0x13 and 5): own size + the other's + a margin. */
f32 BtlCharApi_GetCloseRange(s32 objId);

/* 1.0 when the object exists, else 0.0. No caller. */
f32 BtlCharApi_ObjExistsF(s32 objId);

/* Fighter flag 0x13: the opponent is within the close range. No caller in the main executable. */
s32 BtlCharApi_IsClose(s32 objId);

/* Fighter flag 0xBA: the stage blocks the line between the two fighters' heads. */
s32 BtlCharApi_IsSightBlocked(s32 objId);

/* Fighter flag 0xF: standing on the ground. No caller (the copy at 0x2081E8 is the one used). */
s32 BtlCharApi_IsOnGround(s32 objId);

/* Fighter flag 0x11: the body centre is under water. */
s32 BtlCharApi_IsInWater(s32 objId);

/* Whether the object lacks the "drawn" flag (bit 1 of its flag word). */
s32 BtlCharApi_IsHidden(s32 objId);

/* Whether the fighter is frozen by hit-stop. No caller. */
s32 BtlCharApi_IsFrozen(s32 objId);

/* Whether any fighter is frozen by hit-stop. No caller. */
s32 BtlCharApi_AnyFrozen(void);

/* 1 for a character with parameter flag 0x800 that is not in flag 0xA, else flag 9 (fast vertical flight). */
s32 BtlCharApi_TestStageBreakA(s32 objId);

/* Flag 0xA unless flag 0x21 or 0x22 is up. */
s32 BtlCharApi_TestStageBreakB(s32 objId);

/* How far the fighter has charged: the larger of the attack charge (+0xD78) and the charged ki blast's (+0xDEC), 0..1. */
f32 BtlCharApi_GetChargeRate(s32 objId);

/* A class of the current action for the effect code: 3 fast ascent / leaving switch, 4 fast descent / lift throw,
   5 rush sequence, else 1. */
s32 BtlCharApi_GetActionFxKind(s32 objId);

/* Balance of clash A (roster +0x5C): the lead squashed into -0.8..0.8. */
f32 BtlCharApi_GetClashBias(void);

/* Fighter counter +0xFFC as a 0..1 ratio of 90. */
f32 BtlCharApi_GetBlindRatio(s32 objId);

/* During a rush sequence: 0 when the rush has no marked step (attacker: throw word +0x48 / +0x10 - 1; victim: +0x4C /
   +0x1C), 2 before that step, 1 from it on; -1 outside a rush sequence. */
s32 BtlCharApi_GetRushFinishPhase(s32 objId);

/* BtlObj_AddPush(obj, (sin yaw, 0, cos yaw) * len, arg). No caller. */
void BtlCharApi_ObjPushYaw(s32 objId, f32 yaw, f32 len, f32 arg);

/* BtlObj_AddPush(obj, dir scaled to length len, arg); nothing for a direction shorter than 0.0001. No caller. */
void BtlCharApi_ObjPushDir(s32 objId, Vec4 *dir, f32 len, f32 arg);

/* Body radius: the parameter float +0xC when positive, else object +0xFF0 * 1.8. */
f32 BtlCharApi_GetRadius(s32 objId);

/* Copies the vector the object's +0xFA0 points at (the body position used for pushing apart). */
void BtlCharApi_GetBodyPos(s32 objId, Vec4 *out);

/* Unit direction from `from` to the opponent's model node `node`, with its pitch kept between minPitch and
   maxPitch (a direction steeper than that is flattened, or rebuilt from the model yaw when nearly vertical). A
   technique with flag 0x40000 aims along the heading yaw instead; a direction pointing away from the opponent is
   mirrored; a zero direction becomes the model's facing. */
void BtlCharApi_CalcAimDir(s32 objId, s32 node, Vec4 *from, Vec4 *out, f32 minPitch, f32 maxPitch);

/* The same for node 0x11 and 45 degrees up or down. */
void BtlCharApi_CalcAimDir45(s32 objId, Vec4 *from, Vec4 *out);

/* A random direction for something knocked away by the fighter: its facing turned by two random angles that depend
   on its animation (0xF9, 0xFA, 0xFB / 0x19, 0xFC), else a cone of 0.3 rad round the direction to the opponent.
   Two draws of the fighter generator. */
void BtlCharApi_GetDeflectDir(s32 objId, Vec4 *out);

/* Fighter flag 5: locked on to the opponent. */
s32 BtlCharApi_IsLockedOn(s32 objId);

/* Fighter flag 0x8E. */
s32 BtlCharApi_IsChargingKiBlast(s32 objId);

/* Whether the fighter is in a technique action (0x105..0x132). */
s32 BtlCharApi_IsInTechnique(s32 objId);

/* In a technique action while the previous action (+0x950) was not one. No caller. */
s32 BtlCharApi_EnteredTechnique(s32 objId);

/* Fighter flag 0xA1 (raised when the damage of a rush technique is set up). */
s32 BtlCharApi_IsRushConnected(s32 objId);

/* Whether the fighter is in a rush sequence action (0x12D..0x12F, 0x139..0x13B). */
s32 BtlCharApi_IsInRushSequence(s32 objId);

/* Whether the fighter is in a skill action (0xFD..0x102). */
s32 BtlCharApi_IsInSkill(s32 objId);

/* In a skill action on the frame it was entered (flag 8). No caller. */
s32 BtlCharApi_IsSkillStart(s32 objId);

/* Fighter flag 0x9A (raised on the frame a skill takes effect). */
s32 BtlCharApi_IsSkillApplied(s32 objId);

/* Whether the fighter is in a clash A action (0x130..0x132). */
s32 BtlCharApi_IsInClashA(s32 objId);

/* Whether the fighter is in action 0xFA (clash B) or 0xFC (a clash C exchange). */
s32 BtlCharApi_IsInClashBC(s32 objId);

/* Fighter flag 0xC (raised by the ki charge loop). No caller. */
s32 BtlCharApi_IsChargingKi(s32 objId);

/* Fighter flag 0xD (raised when the ki charge goes on into the powered-up state). No caller. */
s32 BtlCharApi_IsMaxPowerStart(s32 objId);

/* Whether the fighter is transforming, fusing or switching (0xEC..0xF8) or in action 0x103 / 0x104. */
s32 BtlCharApi_IsChanging(s32 objId);

/* Bit 4 of the table word of the fighter's animation. */
s32 BtlCharApi_TestAnimFlag10(s32 objId);

/* Whether the fighter is in action 0x33. */
s32 BtlCharApi_IsCircleDash(s32 objId);

/* Fighter flag 0x12B (raised when the fighter is bound to its object). */
s32 BtlCharApi_IsModelNew(s32 objId);

/* Parameter flag 0x40 with object flags 0x22, or parameter flag 0x80 with object flags 0x42. */
s32 BtlCharApi_HasWeaponOut(s32 objId);

