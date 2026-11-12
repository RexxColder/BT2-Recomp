#define BtlAct_Update func_002CD380  /* fix_targets */ /* the original uses 0x2cd380 here */
#define BtlAnim_ApplyBlend func_002CD408  /* fix_targets */ /* the original uses 0x2cd408 here */
#define BtlMove_ResetAnimStep func_002CD2D8  /* fix_targets */ /* the original uses 0x2cd2d8 here */
#include "common.h"
#include "battle/btl_char_move.h"

/* Fighter movement, 0x1DC9A0-0x1E0290 (see battle/btl_char_move.h for the model and the structures).
 *
 * Called from: BtlChar_UpdateMotion (func_002CD2A8), BtlChar_UpdateStage7 (BtlMove_PushOut,
 * BtlMove_ApplyOrbit), BtlChar_UpdateStage8 (BtlMove_ClampToStage), BtlChar_UpdateLate (BtlMove_UpdateAnimVoice),
 * BtlAct_UpdateTimers (BtlMove_ApplyImpulse, BtlMove_UpdateHoverOffset, BtlMove_UpdateDefenseTimers); everything
 * else is called by the action handlers (0x1E2... onwards).
 */

/* Speeds are written in km/h and converted to metres per frame; angles in degrees. Both macros reproduce the
   original constants bit for bit (see the header). */
#define BTL_KMH(x) ((x) * 1000.0f / 3600.0f * (1.0f / 30.0f))
#define BTL_DEG(x) ((x) / 180.0f * 3.14159265f)
#define BTL_PITCH_MAX (1.5707963f - 0.01f)
#define BTL_IMPULSE_DECEL (BTL_KMH(2000.0f) * (1.0f / 30.0f))

extern f32 atan2f(f32 y, f32 x);
extern f32 sqrtf(f32 x);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern f32 Vec3_Length(Vec4 *v);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec4_SetZero(Vec4 *dst);
extern void Vec4_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t);
extern void Vec4_RotateEuler(Vec4 *dst, Vec4 *angles, Vec4 *src);
extern f32 Mathf_Sin(f32 a);
extern f32 Mathf_Cos(f32 a);
extern f32 Mathf_Asin(f32 a);
extern f32 Mathf_Acos(f32 a);

extern f32 BtlUtil_WrapAngle(f32 a);
extern f32 BtlUtil_LengthXZ(Vec4 *v);
extern f32 BtlUtil_ApproachF(f32 cur, f32 goal, f32 step);
extern f32 BtlUtil_ClampF(f32 v, f32 lo, f32 hi);
extern f32 BtlUtil_MinF(f32 a, f32 b);
extern f32 BtlUtil_MaxF(f32 a, f32 b);

extern s32 BtlChar_TestFlag(BtlMoveChr *chr, s32 flag);
extern void BtlChar_SetFlag(BtlMoveChr *chr, s32 flag);
extern void BtlChar_SetHeldFlag(BtlMoveChr *chr, s32 flag);
extern void BtlChar_ClearFlag(BtlMoveChr *chr, s32 flag);
extern BtlMovePose *BtlChar_GetPos(BtlMoveChr *chr);
extern BtlMoveObj *BtlChar_GetObj(BtlMoveChr *chr);
extern void BtlChar_PlayVoice(BtlMoveChr *chr, s32 kind);
extern s32 BtlInput_IsHeld(BtlMoveChr *chr, u32 mask);

extern s32 BtlAnim_TestAttr(BtlMoveChr *chr, u64 mask);
extern void BtlCharSnd_PlayStream(BtlMoveChr *chr, s32 id);
extern void BtlAnim_SetUnkC8C(BtlMoveChr *chr, f32 v);
extern void BtlAnim_SetStep(BtlMoveChr *chr, f32 v);
extern void BtlAnim_ApplyBlend(BtlMoveChr *chr);
extern void BtlAct_Update(BtlMoveChr *chr);
extern BtlMoveBlastList *EftHit_GetList(void);
extern s32 BtlParam_GetCount80(BtlMoveChr *chr);
extern s32 BtlParam_GetUnk82(BtlMoveChr *chr);
extern f32 BtlInput_GetStickX(BtlMoveChr *chr);
extern f32 BtlInput_GetStickY(BtlMoveChr *chr);
extern f32 BtlOpp_GetYaw(BtlMoveChr *chr);
extern void BtlOpp_GetTargetRot(BtlMoveChr *chr, Vec4 *out);
extern void BtlOpp_GetDelta(BtlMoveChr *chr, Vec4 *out);
extern void BtlOpp_GetPoseVec30(BtlMoveChr *chr, Vec4 *out);
extern f32 BtlOpp_GetHalfHeightDiff(BtlMoveChr *chr);
extern f32 BtlOpp_GetRadius(BtlMoveChr *chr);
extern f32 BtlCharApi_GetRadius(s32 objId);
extern void BtlOpp_GetTargetPos(BtlMoveChr *chr, Vec4 *out);
extern void BtlOpp_GetVelocity(BtlMoveChr *chr, Vec4 *out);
extern void BtlOpp_GetObjVecFA0(BtlMoveChr *chr, Vec4 *out);
extern void BtlCharApi_GetBodyPos(s32 objId, Vec4 *out);
extern void BtlChar_SetUnk1310(BtlMoveChr *chr, Vec4 *v);
extern f32 BtlStage_GetInnerRadius(void);
extern f32 BtlStage_GetTop(void);
extern f32 BtlStage_GetBottom(void);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern f32 BtlOpp_GetHeight(BtlMoveChr *chr);
extern void BtlChar_GetSnapPos(BtlMoveChr *chr, Vec4 *out, s32 slot);
extern void BtlOpp_GetSnapPos(BtlMoveChr *chr, Vec4 *out, s32 slot);
extern void BtlChar_GetSnapDelta(BtlMoveChr *chr, Vec4 *out, s32 a, s32 b);
extern s32 BtlChars_IsTimeStopped(void);
extern s32 BtlInput_TestAction(BtlMoveChr *chr, s32 id, s32 arg);
extern f32 BtlMember_GetHealthRatio(BtlMoveChr *chr);
extern s32 BtlMember_HasAbility(BtlMoveChr *chr, s32 ability);
extern s32 BtlParam_GetFlags2(BtlMoveChr *chr);
extern s32 BtlChar_IsDead(BtlMoveChr *chr);
extern s32 BtlChar_IsFree(BtlMoveChr *chr);
extern s32 BtlChar_IsStage4Or27(void);
extern void ColSeg_Set(BtlMoveSeg *seg, Vec4 *a, Vec4 *b);
extern s32 StgCol_TraceSegment(BtlMoveSeg *seg);
extern void StgCol_GetHitPos(Vec4 *out);

/* Late per-frame voice triggers: with flags 0x12F..0x133 the current animation's attribute bits pick a voice kind
   (0xE, 0x34..0x37) or a stream (0x8D35, 0x8D37, 0x8D41, 0x8D42). Called from BtlChar_UpdateLate. */
void BtlMove_UpdateAnimVoice(BtlMoveChr *chr);

/* Resets the object's animation rates before the action handlers run: obj+0xC8C = 0, step (obj+0xC80) = 2. */
void BtlMove_ResetAnimStep(BtlMoveChr *chr);

/* First call of a fighter's main update (BtlChar_UpdateMotion): runs the action state machine between the
   animation rate reset and the blend update. */
void func_002CD2A8(BtlMoveChr *chr) {
    BtlMove_ResetAnimStep(chr);
    BtlAct_Update(chr);
    BtlAnim_ApplyBlend(chr);
}

/* Tests the two stage contacts of this frame: the ground under the fighter (flag 0xF, normal at pose+0xC0) and the
   object's second contact (flag 0x1F without 0x20, normal at work+0x18070). floor = 1 keeps normals within 45 degrees
   of straight up (n.y <= -0.707), floor = 0 keeps the others. Returns 1 when one is kept and the direction of travel
   points into it by more than cos(angle) (angle = -2 pi: any direction). */
s32 BtlMove_TestContact(BtlMoveChr *chr, s32 floor, f32 angle);

/* The contact test for floor-like surfaces. */
s32 BtlMove_IsHeadingIntoFloor(BtlMoveChr *chr, f32 angle);

/* The contact test for wall-like surfaces. */
s32 BtlMove_IsHeadingIntoWall(BtlMoveChr *chr, f32 angle);

/* Counts the fighter's live blasts of one class (0: definition kinds 0, 4, 8; 1: the others), stores the count and
   returns 1 while it is below the character's limit for the class (BtlParam_GetCount80 / BtlParam_GetUnk82). */
s32 BtlMove_CanFireBlast(BtlMoveChr *chr, s32 mode, s32 *outCount);

/* Returns 1 when a live blast record of an enabled class (a: kinds 0/4/8, b: other kinds, c: type-1 records) is
   moving towards the fighter and would reach it within `limit` frames at its current speed. */
s32 BtlMove_IsBlastIncoming(BtlMoveChr *chr, s32 a, s32 b, s32 c, f32 limit);

/* Number of type-1 blast records whose source belongs to this fighter. */
s32 BtlMove_CountOwnBeams(BtlMoveChr *chr);

/* Where the segment from -> to crosses the circle of the given radius around the stage centre (XZ plane, the
   later root): writes the point and returns 1, or returns 0 when it does not cross. */
s32 BtlMove_ClipToRadius(Vec4 *out, Vec4 *from, Vec4 *to, f32 radius);

/* Turns the heading yaw towards a target by at most maxStep. Modes: 0 stick relative to the camera yaw,
   1 stick x as a turn rate, 2 / 4 towards the opponent, 3 away from it, 7 towards the stage centre, 8 away from the
   centre, 9 the opponent's own yaw, 5 / 6 keep. Also clears the yaw steering offset. */
void BtlMove_TurnYaw(BtlMoveChr *chr, s32 mode, f32 maxStep);

/* Turns the heading pitch towards a target by at most maxStep. Modes: 0 stick y as a rate (clamped to +-(pi/2 - 0.01)),
   1..4 at the opponent (2 scaled by the stick, 3 doubled height, 4 flattened under 50 m), with the height
   difference reduced when the two are about to meet; 5 level; 6 keep. Also clears the pitch steering offset. */
void BtlMove_TurnPitch(BtlMoveChr *chr, s32 mode, f32 maxStep);

/* Homing dash: heads for the opponent with a stick-controlled offset. The offset goal is (pi/2 * stick), scaled down
   when under 2 frames from contact, clamped to yawMax / pitchMax and approached by yawAccel / pitchAccel per frame.
   Without lock-on only clears the offsets. */
void BtlMove_SteerAtOpponent(BtlMoveChr *chr, f32 closeSpeed, f32 yawAccel, f32 pitchAccel, f32 yawMax, f32 pitchMax, f32 maxStep);

/* Turns the model yaw (rot.y) towards the heading yaw: step = |difference| * rate, at least 1.8 degrees, at most maxStep. */
void BtlMove_TurnModelYaw(BtlMoveChr *chr, f32 maxStep, f32 rate);

/* Sets heading yaw and pitch, and the model yaw, at once. */
void BtlMove_SetHeading(BtlMoveChr *chr, f32 yaw, f32 pitch);

/* Turns the heading towards a world point by at most yawStep / pitchStep and clears the steering offsets. */
void BtlMove_TurnToPoint(BtlMoveChr *chr, Vec4 *target, f32 yawStep, f32 pitchStep);

/* Builds the unit direction of travel. Modes: 0 stick rotated by the camera yaw (horizontal), 1 the same tilted by
   the heading pitch, 2 heading yaw, 3 heading yaw and pitch, 4 / 5 the reverse of 2 / 3, 6 keep (horizontal part),
   7 keep. With no stick input modes 0 / 1 keep the old direction. */
void BtlMove_SetDirection(BtlMoveChr *chr, s32 mode);

/* The integration step: speed approaches the target by accel, then pos += dir * speed. */
void BtlMove_Advance(BtlMoveChr *chr, f32 speed, f32 accel);

/* One frame of ordinary movement, used by most action handlers: turn the heading instantly, turn the model
   (36 degrees per frame at most), rebuild the direction, advance. */
void BtlMove_Step(BtlMoveChr *chr, s32 yawMode, s32 pitchMode, s32 dirMode, f32 speed, f32 accel);

/* Lock-on only: places the fighter on the opponent's path, `lead` frames ahead plus both radii, inside the stage radius. */
void BtlMove_WarpAheadOfOpponent(BtlMoveChr *chr, f32 lead);

/* Lock-on only: places the fighter behind the opponent (its next position, both radii plus gap away). */
void BtlMove_WarpBehindOpponent(BtlMoveChr *chr, f32 gap);

/* Lock-on only: places the fighter in front of the opponent. */
void BtlMove_WarpInFrontOfOpponent(BtlMoveChr *chr, f32 gap);

/* Moves the fighter so that its object's body point coincides with the opponent's, stops it and raises flags 0x3F
   (no push-out), 0x24 (no velocity this frame) and 0x55 with the point saved at chr+0x1310. */
void BtlMove_SnapToOpponent(BtlMoveChr *chr);

/* Flies around the opponent on a 200 m circle towards the point opposite baseYaw (side 0 / 1 picks the way round),
   clipped to the stage radius. Returns 1 on the frame the target point is reached. */
s32 BtlMove_CircleOpponent(BtlMoveChr *chr, s32 side, s32 lead, f32 baseYaw, f32 speed);

/* Computes where to go to attack the opponent from a given elevation angle: the opponent's predicted position
   (lead frames ahead, stopped by the stage, kept between the stage's top and bottom), and a point `dist` away
   from it on the fighter's side. */
void BtlMove_CalcApproachPoint(BtlMoveChr *chr, Vec4 *out, Vec4 *outTarget, f32 dist, f32 angle, f32 distScale, f32 lead);

/* Gravity: vertical speed += 50 km/h per frame up to 3000 km/h, then y += speed (+Y is down). */
void BtlMove_Fall(BtlMoveChr *chr);

/* Vertical speed approaches a target by accel, then y += speed. */
void BtlMove_MoveVertical(BtlMoveChr *chr, f32 speed, f32 accel);

/* Brings the vertical speed to 0 by 100 km/h per frame. */
void BtlMove_BrakeVertical(BtlMoveChr *chr);

/* Vertical part of ordinary movement: in flight (flag 0xE) the vertical speed is braked, otherwise the fighter falls. */
void BtlMove_ApplyGravity(BtlMoveChr *chr);

/* Sets the model's forward lean, clamped to +-(pi/2 - 0.01). */
void BtlMove_SetLeanX(BtlMoveChr *chr, f32 v);

/* Sets the model's sideways lean. */
void BtlMove_SetLeanZ(BtlMoveChr *chr, f32 v);

/* 1 when the push-out moved the fighter this frame (flag 0x5E) and the two overlap in height (or flag 0x5F). */
s32 BtlMove_IsBlockedByOpponent(BtlMoveChr *chr);

/* Stage 8: keeps the position inside the stage's limit cylinder and raises the contact flags: 0x14 radius,
   0x15 top, 0x16 bottom, 0x17 the y = -10 limit of stages 4 / 27. */
void BtlMove_ClampToStage(BtlMoveChr *chr);

/* Lock-on only: asks for this frame's movement to be bent into an orbit (flag 0x19) between two distances. */
void BtlMove_RequestOrbit(BtlMoveChr *chr, f32 near, f32 far);

/* Stage 7: with flag 0x19, removes the change of distance to the opponent from this frame's movement and turns
   the heading by the angle travelled, fully beyond `far`, not at all inside `near`. */
void BtlMove_ApplyOrbit(BtlMoveChr *chr);

/* Stage 7: keeps the fighter out of the opponent's body: a vertical plane between the two, placed by both radii,
   shared between them in proportion to how much each moved towards the other this frame. */
s32 BtlMove_PushOut(BtlMoveChr *chr);

/* Vertical speed that covers `height` when it is afterwards braked by 100 km/h per frame, plus extra, limited to
   +-800 km/h. */
f32 BtlMove_CalcVerticalSpeed(f32 height, f32 extra);

/* Sets the vertical speed so that the fighter ends at the opponent's height. */
void BtlMove_AimVerticalAtOpponent(BtlMoveChr *chr, s32 lead);

/* Take-off: once (flag 0x8A) faces the opponent, enters flight (0xE) and aims for its height; raises 0x81, 0x82, 0x8A. */
void BtlMove_BeginRiseToOpponent(BtlMoveChr *chr);

/* Upward launch speed (negative) that rises `height` against gravity. */
f32 BtlMove_CalcJumpSpeed(f32 height);

/* Sets the impulse velocity (knock-back) unless the current one is larger. */
void BtlMove_SetImpulse(BtlMoveChr *chr, Vec4 *vel);

/* Impulse along a direction. */
void BtlMove_SetImpulseDir(BtlMoveChr *chr, Vec4 *dir, f32 speed);

/* Horizontal impulse along a yaw. */
void BtlMove_SetImpulseYaw(BtlMoveChr *chr, f32 yaw, f32 speed);

/* After touching the stage limit: heads along the wall (or the reverse), and removes the pitch into the top / bottom. */
void BtlMove_DeflectAtStageLimit(BtlMoveChr *chr, s32 back);

/* Per frame: pos += impulse, then the impulse loses BTL_IMPULSE_DECEL of length. Declared int with no return value:
   the original does not tail-call. */
s32 BtlMove_ApplyImpulse(BtlMoveChr *chr);

/* Per frame: the display offset (pose+0x20): hover bob 2 * sin(phase) while flying idle, and a sideways shake. */
void BtlMove_UpdateHoverOffset(BtlMoveChr *chr);

/* Per frame: the seven defence windows at chr+0x1068: each counts down to a floor and is re-opened by its input. */
void BtlMove_UpdateDefenseTimers(BtlMoveChr *chr);
