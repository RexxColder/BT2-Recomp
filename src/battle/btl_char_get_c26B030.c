#include "common.h"
#include "battle/btl_char_get.h"

/*
 * Battle helpers and fighter accessors: 0x1DBF20..0x1DC9A0.
 * Scalar helpers first, then the roster lookups, the fighters' frame counter and random generator,
 * pad vibration and voice lines. The object file this belongs to is larger (its float constants run on
 * from 0x1DBAD0's and into 0x1DCB88's), so the range is a slice of it, not a whole source file.
 */

extern f32 sqrtf(f32 x);
extern f32 sinf(f32 x);
extern void *BtlObj_Get(s32 id);
extern void BtlObj_SetSubState(void *obj, s32 state, s32 arg);
extern s32 BtlChar_TestFlag(BtlCharGetChr *chr, s32 bit);
extern s32 BattleReplay_IsActive(void);
extern s32 Battle_GetStage(void);
extern s32 Battle_GetMode(void);
extern s32 Voice_IsStopped(s32 voice);
extern void Voice_Stop(s32 voice);
extern BtlCharGetVitals *BtlMember_GetActiveGauge(BtlCharGetChr *chr); /* active member's block + 0x40 */
extern s32 BtlChars_IsTimeStopped(void);                             /* gBtlChars + 0x274 */
extern void BtlCharSnd_PlayOwn(BtlCharGetChr *chr, s32 line);    /* sound request, channel chr->player + 2 */
extern void BtlCharSnd_PlayVoice(BtlCharGetChr *chr, s32 line);    /* sound request, channel chr->player + 5 */
extern void BtlCharSnd_StopOwn(BtlCharGetChr *chr, s32 line);
extern s32 BtlScript_IsTextShown(void);

extern BtlCharGetRoster *gBtlChars;

/* Brings an angle back into -pi..pi (one turn at most). */
f32 func_0026B030(f32 a) {
    if (a < -3.14159265f) {
        a += 6.2831853f;
    }
    if (a > 3.14159265f) {
        a -= 6.2831853f;
    }
    return a;
}

/* Wraps the three angles of src into dst; w is copied. */
void BtlUtil_WrapAngles(Vec4 *dst, Vec4 *src);

/* Horizontal length of a vector. */
f32 BtlUtil_LengthXZ(Vec4 *v);

/* Moves cur toward target by |step| without passing it. */
f32 BtlUtil_ApproachF(f32 cur, f32 target, f32 step);

/* Integer form of BtlUtil_ApproachF. */
s32 BtlUtil_Approach(s32 cur, s32 target, s32 step);

/* Clamps v to lo..hi. */
f32 BtlUtil_ClampF(f32 v, f32 lo, f32 hi);

/* Smaller of two floats. */
f32 BtlUtil_MinF(f32 a, f32 b);

/* Larger of two floats. */
f32 BtlUtil_MaxF(f32 a, f32 b);

/* Clamps v to lo..hi. */
s32 BtlUtil_Clamp(s32 v, s32 lo, s32 hi);

/* Smaller of two integers. */
s32 BtlUtil_Min(s32 a, s32 b);

/* Larger of two integers. */
s32 BtlUtil_Max(s32 a, s32 b);

/* Rounds n up to a multiple of unit. */
s32 BtlUtil_RoundUp(s32 n, s32 unit);

/* Quarter-turn sector of an angle: 0 around 0, 2 around -pi/2, 3 around +pi/2, 1 around +-pi. */
s32 BtlUtil_AngleToSector(f32 a);

/* Number of fighters. */
s32 BtlChar_GetCount(void);

/* Fighter i. */
BtlCharGetChr *BtlChar_Get(s32 i);

/* Fighter that owns battle object objId, or NULL. */
BtlCharGetChr *BtlChar_FindByObjId(s32 objId);

/* Fighter whose side word is `side`, or NULL. */
BtlCharGetChr *BtlChar_FindBySide(s32 side);

/* The fighter's battle object. */
void *BtlChar_GetObj(BtlCharGetChr *chr);

/* Address of the fighter's position. */
Vec4 *BtlChar_GetPos(BtlCharGetChr *chr);

/* The fighter's controller. */
Pad *BtlChar_GetPad(BtlCharGetChr *chr);

/* 1 while the fighter's freeze counter is running. */
s32 BtlChar_IsFrozen(BtlCharGetChr *chr);

/* 1 when the fighter is alive, flag 0xBE is clear and counter 0xFE0 has run out. */
s32 BtlChar_IsFree(BtlCharGetChr *chr);

/* 1 when the active member has no health left. */
s32 BtlChar_IsDead(BtlCharGetChr *chr);

/* 1 when the active member's word 0x70 is set. */
s32 BtlChar_TestMemberUnk70(BtlCharGetChr *chr);

/* Frames simulated since the fighters were reset. No caller. */
s32 BtlChar_GetFrame(void);

/* Frame counter modulo n (n < 1 counts as 1): the cheap "random" pick used for voice lines and the like. */
s32 BtlChar_FrameMod(s32 n);

/* The fighters' random generator: 0..150888. The state is kept unchanged while roster+0x274 is set. */
s32 BtlChar_Rand(void);

/* BtlChar_Rand as a float in 0..1. */
f32 BtlChar_RandF(void);

/* 1 on stages 4 and 27. */
s32 BtlChar_IsStage4Or27(void);

/* On stages 4 and 27, adds time to the roster's stage timer (at most 150 frames). */
void BtlChar_AddStageTimer(f32 seconds);

/* Asks for big-motor vibration; a weaker request does not replace a running stronger one. */
void BtlChar_SetVibration(BtlCharGetChr *chr, f32 power, f32 seconds);

/* Asks for small-motor vibration; only ever lengthens it. */
void BtlChar_SetSmallVibration(BtlCharGetChr *chr, f32 seconds);

/* Both motors. */
void BtlChar_Vibrate(BtlCharGetChr *chr, f32 power, f32 seconds);

/* Per frame: sends the fighter's vibration to its pad. Nothing when disabled, in a replay or for a CPU. */
void BtlChar_UpdateVibration(BtlCharGetChr *chr);

/* Entry of the voice table for a kind. */
BtlVoiceEntry *BtlChar_GetVoiceEntry(s32 kind);

/* Plays one of the lines of a voice kind unless the fighter is dead or the kind is cooling down. */
void BtlChar_PlayVoice(BtlCharGetChr *chr, s32 kind);

/* Stops the fighter's voice while flag 0x129 is set (in mode 1 only when BtlScript_IsTextShown returns 0). */
void BtlChar_StopVoiceOnFlag(BtlCharGetChr *chr);

/* Per frame: counts the voice cooldowns down. */
void BtlChar_TickVoiceTimers(BtlCharGetChr *chr);

/* Plays the line of a voice kind that has only one, through BtlCharSnd_StopOwn. */
void BtlChar_PlayVoiceSingle(BtlCharGetChr *chr, s32 kind);
