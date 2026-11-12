#include "common.h"
#include "battle/btl_char_member.h"

/*
 * Team members, parameters and gauges of a fighter: 0x1CDCA8..0x1CF578.
 *
 *   0x1CDD40..0x1CE630  member entries: parameter load, lookups, the active member, the switch candidate
 *   0x1CE630..0x1CF220  health, ki, blast stock and the +0x1C gauge of the active member; abilities
 *   0x1CF220            per-frame queued damage and drain
 *   (0x1CF578..0x1D00D8, the one-frame effect request bits and the effects / sounds they spawn, is the first part
 *   of src/battle/btl_char_fx.c: BtlFx_UpdateGroundFx needs the request-bit helpers in its translation unit)
 *
 * Units: health 10000 per bar; ki 0..100000; blast stock 100000 per stock; the +0x1C gauge 0..30000.
 * Nothing here regenerates a gauge over time: this module only offers the add / spend calls. The per-frame
 * function (BtlMembers_UpdateQueuedDamage) applies damage and drain that a fighter queued against its opponent.
 * No random draw is made by the gauge code; the effect code picks sound variants with BtlChar_FrameMod.
 *
 * The file starts at 0x1CDCA8 with BtlColl_NextPoolMember: BtlMember_Damage only compiles to the original bytes
 * when that callee is defined earlier in the same file, so the original object starts there or earlier.
 *
 * Callees outside this file, as far as this file shows what they are:
 *   BtlAnim_GetFlags(BtlAnim_GetId(chr))  flags of the current animation: 0x800 halves damage taken, 8 without 0x10
 *                                         is the window in which queued drain runs
 *   BtlAnim_TestAttr(chr, 1 << 33)        the animation's "deal the queued hit now" event
 *   BtlOpp_HasAbility(chr, n)              BtlMember_HasAbility(the opponent, n)
 *   BtlParam_GetDamageTakenScale(chr)                    float at (object + 0x91C) + 0x7C: the character's damage-taken multiplier
 *   BtlStat_GetScale7(chr)                second damage-taken multiplier, from the member's bonus level
 *   BtlColl_NextPoolMember(chr)                    side 1 in mode 3: brings in the next opponent of the pool (BtlMember_Replace)
 *   EftShot_Request / EftTransform_Start / EftTransform_Flash / EftTransform_End / EftImpact_SpawnHit   effect spawners
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

/* Opponent queue of mode 3 (battle work + 0x5A8); local view of BattleMemberPool. */
typedef struct BtlMemberPool {
    /* 0x00 */ s32 cur;
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 members[50][0x64];
} BtlMemberPool;

extern BtlMemberPool *Battle_GetWork5A8(void);

/* Mode 3: brings in the next opponent of the pool for side 1. 0x1CDCA8, in front of the member code proper: it is
 * the first function of this file because BtlMember_Damage only compiles to the original bytes with it defined
 * above (the functions before it are src/battle/btl_char_coll_b.c). */
void BtlColl_NextPoolMember(BtlMemberChr *chr);

/* Loads a member's gauge maxima from the character table and its abilities; with init also the starting values. */
void BtlMember_LoadParams(BtlMemberChr *chr, s32 member, s32 init, f32 healthPct, s32 variant);

/* Returns member entry n. */
BtlMember *BtlMember_Get(BtlMemberChr *chr, s32 n);

/* Returns the entry of the member that is fighting. */
BtlMember *BtlMember_GetActive(BtlMemberChr *chr);

/* Returns the present member that is the given character, or NULL. */
BtlMember *BtlMember_FindPresent(BtlMemberChr *chr, s32 chara);

/* Returns the index of the present member that is the given character, or -1. */
s32 BtlMember_FindPresentIndex(BtlMemberChr *chr, s32 chara);

/* Returns the gauge block of member n. */
BtlMemberGauge *BtlMember_GetGauge(BtlMemberChr *chr, s32 n);

/* Returns the gauge block of the member that is fighting. */
BtlMemberGauge *BtlMember_GetActiveGauge(BtlMemberChr *chr);

/* Rebuilds the first defeated, non-active slot from a setup member; returns the slot or -1. */
s32 BtlMember_Replace(BtlMemberChr *chr, BtlMemberSetup *src);

/* Returns the index of the member that is the given character (present or not), or -1. */
s32 BtlMember_FindIndex(BtlMemberChr *chr, s32 chara);

/* Sets which member is fighting. */
void BtlMember_SetActiveIndex(BtlMemberChr *chr, s32 n);

/* Counts the present members that still have health. */
s32 BtlMember_CountAlive(BtlMemberChr *chr);

/* Returns which member is fighting. */
s32 BtlMember_GetActiveIndex(BtlMemberChr *chr);

/* Returns the switch candidate after moving it off a defeated member and off the active one. */
s32 BtlMember_GetSwitchTarget(BtlMemberChr *chr);

/* Sets the switch candidate; returns 1 if it was acceptable as given. */
s32 BtlMember_SetSwitchTarget(BtlMemberChr *chr, s32 n);

/* Moves the switch candidate to the next living member that is not fighting. */
void BtlMember_NextSwitchTarget(BtlMemberChr *chr);

/* Moves the switch candidate to the previous living member that is not fighting. */
void BtlMember_PrevSwitchTarget(BtlMemberChr *chr);

/* Takes health from the active member after every modifier; returns the health actually lost.
 *
 * In order: halved when the current animation has flag 0x800; combo scaling from the 5th hit (3% less per hit down to
 * 50%, or 2% down to 70% when the attacker has ability 0x5D); the two defense multipliers (a non-zero amount never
 * drops below 1); drain is cancelled by ability 0x3F and halved by 0x3E; ability 0x76 takes no damage at all; nothing
 * happens outside fighter flag 3 unless BTL_DMG_ANY_STATE; amounts of 10 or more are rounded up to a multiple of 10;
 * modes 5 and 6, drain and BTL_DMG_NO_KILL leave at least 1 health. Then the combo counters, the KO events
 * (0x4A for the side, 0x48 and 0x51..0x53 for the opponent), event 0x59 for any loss, and on reaching 0 the ki, blast
 * and +0x1C gauges are emptied.
 */
/* Only matches with BtlColl_NextPoolMember defined above in this file (bgtz, not bgtzl, after BtlMember_CountAlive). */
s32 BtlMember_Damage(BtlMemberChr *chr, s32 amount, s32 flags);

/* Gives health to the active member, up to its maximum. */
void BtlMember_AddHealth(BtlMemberChr *chr, s32 amount);

/* Whether the active member has at least this much health. */
s32 BtlMember_HasHealth(BtlMemberChr *chr, s32 amount);

/* Gives ki to the active member; returns what did not fit. */
s32 BtlMember_AddKi(BtlMemberChr *chr, s32 amount);

/* Whether the active member has at least this much ki. */
s32 BtlMember_HasKi(BtlMemberChr *chr, s32 amount);

/* Spends ki (nothing is spent under flag 6 unless forced); returns 1 if the gauge ran out. */
s32 BtlMember_SpendKi(BtlMemberChr *chr, s32 amount, s32 force);

/* Takes ki away from the active member; returns how much was taken. */
s32 BtlMember_DrainKi(BtlMemberChr *chr, s32 amount);

/* Adds to the blast stock gauge, up to its maximum. */
void BtlMember_AddBlast(BtlMemberChr *chr, s32 amount);

/* Whether the blast stock gauge holds at least this much. */
s32 BtlMember_HasBlast(BtlMemberChr *chr, s32 amount) {
    if (BtlMember_GetActiveGauge(chr)->blast < amount) {
        return 0;
    }
    return 1;
}

/* Spends blast stock, down to 0. */
void BtlMember_SubBlast(BtlMemberChr *chr, s32 amount) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    g->blast -= amount;
    if (g->blast < 0) {
        g->blast = 0;
    }
}

/* Adds to the +0x1C gauge, up to 30000. */
void BtlMember_AddMaxPower(BtlMemberChr *chr, s32 amount) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    g->maxPower += amount;
    if (g->maxPower > 30000) {
        g->maxPower = 30000;
    }
}

/* Subtracts from the +0x1C gauge, down to 0. */
void BtlMember_SubMaxPower(BtlMemberChr *chr, s32 amount) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    g->maxPower -= amount;
    if (g->maxPower < 0) {
        g->maxPower = 0;
    }
}

/* Sets the +0x1C gauge, clamped to 0..30000. */
void BtlMember_SetMaxPower(BtlMemberChr *chr, s32 value);

/* Health of the active member as a fraction of its maximum. */
f32 BtlMember_GetHealthRatio(BtlMemberChr *chr) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    if (g->healthMax > 0) {
        return (f32)g->health / (f32)g->healthMax;
    }
    return 0.0f;
}

/* Health of the whole team as a fraction of the summed maxima. */
f32 BtlMember_GetTeamHealthRatio(BtlMemberChr *chr);

/* Ki of the active member as a fraction of its maximum. */
f32 BtlMember_GetKiRatio(BtlMemberChr *chr) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    if (g->kiMax > 0) {
        return (f32)g->ki / (f32)g->kiMax;
    }
    return 0.0f;
}

/* Whether the active member's health is at its maximum. */
s32 BtlMember_IsHealthFull(BtlMemberChr *chr) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    if (g->health < g->healthMax) {
        return 0;
    }
    return 1;
}

/* Whether the active member's ki is at its maximum. */
s32 BtlMember_IsKiFull(BtlMemberChr *chr) {
    BtlMemberGauge *g = BtlMember_GetActiveGauge(chr);

    if (g->ki < g->kiMax) {
        return 0;
    }
    return 1;
}

/* Whether the +0x1C gauge is at 30000. */
s32 BtlMember_IsMaxPowerFull(BtlMemberChr *chr) {
    if (BtlMember_GetActiveGauge(chr)->maxPower < 30000) {
        return 0;
    }
    return 1;
}

/* Whether the active member has no health left. */
s32 BtlMember_IsHealthEmpty(BtlMemberChr *chr) {
    return BtlMember_GetActiveGauge(chr)->health <= 0;
}

/* Whether the active member has no ki left. */
s32 BtlMember_IsKiEmpty(BtlMemberChr *chr) {
    return BtlMember_GetActiveGauge(chr)->ki <= 0;
}

/* Whether the +0x1C gauge is empty. */
s32 BtlMember_IsMaxPowerEmpty(BtlMemberChr *chr) {
    return BtlMember_GetActiveGauge(chr)->maxPower <= 0;
}

/* Whether the active member has ability bit n. */
s32 BtlMember_HasAbility(BtlMemberChr *chr, s32 n);

/* Whether the given member has ability bit n. */
s32 BtlMember_HasAbilityOf(BtlMemberChr *chr, s32 member, s32 n);

/* Whether the active member has any of eleven listed abilities. */
s32 BtlMember_HasAnyListedAbility(BtlMemberChr *chr);

/* Per frame: deals the damage each fighter has queued against its opponent, and runs its health / ki drain. */
void BtlMembers_UpdateQueuedDamage(void);
