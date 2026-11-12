#define BtlPause_Term func_00304690  /* fix_targets */ /* the original uses 0x304690 here */
#include "common.h"
#include "battle/btl_tech_b.h"

/*
 * Character data accessors, 0x20F0E8..0x2129C8 (the continuation of btl_tech_a.c; see include/battle/btl_tech_b.h
 * for the tables and the slot model). Five groups, in address order:
 *   0x20F0E8  BtlParam_*      tail of the general parameter block (obj + 0x91C)
 *   0x20F530  BtlKiBlast_*    the 13 ki blast records (obj + 0x924)
 *   0x210940  BtlMoveParam_*  movement speeds, turn rates and ki costs (obj + 0x928)
 *   0x210CD8  BtlSuper_*      techniques of slots 2..4: the two Blast 2 moves and the Ultimate (obj + 0x92C)
 *   0x211FE8  BtlSkill_*      skills of slots 0..1: Blast 1 (obj + 0x930)
 *   0x2128C0  BtlGame_*       five wrappers around the HUD and the battle sequence (probably another source file)
 *
 * Abilities are the 128 bits of the active member (BtlMember_HasAbility); the numbers below are bit numbers.
 * "Curve row n" is BtlStat_GetScaleN: a multiplier of 1 at stat level 0 (rows 6, 9, 10: 3 at level 80, 0.5 at
 * level -20; row 8: 1.3 and 0.925).
 */

/* km/h to units per frame, as btl_char_move.c writes it (the 4000 km/h cap needs this form). */
#define BTL_KMH(x) ((x) * 1000.0f / 3600.0f * (1.0f / 30.0f))
/* The factor the readers of this file multiply a table speed by, after "* 10.0f": 1 km/h in units per frame.
   The constant is one bit above BTL_KMH(1.0f), so it was written as a chain of divisions. */
#define BTL_KMH_PER_FRAME (1000.0f / 3600.0f / 30.0f)

extern BtlTechBRoster *gBtlChars;
extern s32 gBtlGameReplayActive;

extern BtlTechBObj *BtlChar_GetObj(BtlTechBChr *chr);
extern BtlTechBPose *BtlChar_GetPos(BtlTechBChr *chr);
extern BtlTechBChr *BtlChar_Get(s32 i);
extern s32 BtlChar_TestFlag(BtlTechBChr *chr, s32 flag);
extern s32 BtlChar_TestMemberUnk70(BtlTechBChr *chr);
extern s32 BtlUtil_RoundUp(s32 v, s32 unit);
extern s32 BtlMember_HasAbility(BtlTechBChr *chr, s32 n);
extern BtlTechBMember *BtlMember_GetActive(BtlTechBChr *chr);
extern BtlTechBGauge *BtlMember_GetActiveGauge(BtlTechBChr *chr);
extern s32 BtlOpp_HasAbility(BtlTechBChr *chr, s32 n);
extern f32 BtlOpp_GetUnk20F318(BtlTechBChr *chr);
extern void BtlCharSnd_PlayCommon(BtlTechBChr *chr, s32 sound);
extern s32 BtlAct_GetCurrent(BtlTechBChr *chr);
extern s32 BtlAnim_GetId(BtlTechBChr *chr);
extern f32 BtlStat_GetKiBlastDamageScale(BtlTechBChr *chr);
extern f32 BtlStat_GetSpeedScale(BtlTechBChr *chr);
extern f32 BtlStat_GetBlast2DamageScale(BtlTechBChr *chr);
extern f32 BtlStat_GetUltimateDamageScale(BtlTechBChr *chr);
extern s32 BtlParam_GetFlags(BtlTechBChr *chr);
extern s32 BtlParam_GetUnk0(BtlTechBChr *chr);
extern s32 Battle_GetStage(void);
extern s32 Battle_IsSplitScreen(void);
extern s32 BattleReplay_IsActive(void);
extern void BtlSeq_Reset(void);
extern void BtlSeq_Init(void);
extern void BtlSeq_Term(void);
extern void BtlSeq_PreUpdate(void);
extern s32 BtlSeq_Update(void);
extern void PauseMenu_Reset(void);
extern void BtlPause_Reset(void);
extern void Hud_Reset(void);
extern void Hud_Init(void);
extern void PauseMenu_Init(void);
extern void BtlPause_Init(s32 n);
extern void Hud_Term(void);
extern void PauseMenu_Term(void);
extern void BtlPause_Term(void);
extern void Hud_PreUpdate(void);

s32 BtlKiBlast_GetTypeOf(BtlTechBChr *chr, u32 kind);
s32 BtlSuper_GetShots(BtlTechBChr *chr, s32 slot);
s32 BtlSuper_GetHitsB(BtlTechBChr *chr, s32 slot);
s32 BtlSuper_GetHitsC(BtlTechBChr *chr, s32 slot);
s32 BtlSuper_GetStepCount(BtlTechBChr *chr, s32 slot);
s32 BtlSkill_GetShots(BtlTechBChr *chr, s32 slot);
s32 BtlSkill_GetHitsB(BtlTechBChr *chr, s32 slot);
s32 BtlSkill_GetHitsC(BtlTechBChr *chr, s32 slot);

/* ---- general parameters (obj + 0x91C), continued from btl_tech_a.c ------------------------------------------- */

/* Parameter +0x5C (float; no caller found). */
f32 BtlParam_GetUnk5C(BtlTechBChr *chr);

/* Parameter +0x68 (float; BtlAct_StepHandler). */
f32 BtlParam_GetUnk68(BtlTechBChr *chr);

/* Parameter +0x6C (float; BtlAct_StepHandler). */
f32 BtlParam_GetUnk6C(BtlTechBChr *chr);

/* Parameter +0x60: multiplies the reaction scale of a hit this character takes (BtlHit_ApplyHit). */
f32 BtlParam_GetHitReactScale(BtlTechBChr *chr);

/* Parameter +0x70 (s16): copied to fighter +0xD6C every frame. */
s32 BtlParam_GetUnk70(BtlTechBChr *chr);

/* Parameter +0x72 (s16): copied to fighter +0xD74 every frame. */
s32 BtlParam_GetUnk72(BtlTechBChr *chr);

/* Parameter +0x74: attack charge rate at gauge 0 (BtlAct_GetChargeRate); x1.2 with ability 0x4A. */
f32 BtlParam_GetChargeRateA(BtlTechBChr *chr);

/* Parameter +0x78: attack charge rate at a full gauge. */
f32 BtlParam_GetChargeRateB(BtlTechBChr *chr);

/* Parameter +0x7C: multiplier of the damage this character takes (BtlMember_Damage). */
f32 BtlParam_GetDamageTakenScale(BtlTechBChr *chr);

/* Seconds the fighter +0x99C gauge takes to fill: parameter +0x64, / 1.2 (ability 0x34), then x2 (0x1B) or / 0.8 (0x35). */
f32 BtlParam_GetGauge99CTime(BtlTechBChr *chr);

/* Parameter +0xC7 as a fraction (percent * 0.01); x0.5 with ability 0x48, x1.5 with ability 0x49. */
f32 BtlParam_GetUnkC7Scale(BtlTechBChr *chr);

/* Parameter +0xC8 (float; no caller found). */
f32 BtlParam_GetUnkC8(BtlTechBChr *chr);

/* Parameter byte +0x8F + n. */
s32 BtlParam_GetUnk8F(BtlTechBChr *chr, s32 n);

/* Common sound of a dash / burst start: 0x1D with parameter flag 0x10, else 0x1C. */
s32 BtlParam_GetDashSound(BtlTechBChr *chr);

/* Common sound 0x15 (charge start); characters with parameter word 0 bit 0x100 also play 0x3E. */
s32 BtlParam_GetChargeStartSound(BtlTechBChr *chr);

/* Common sound 0x16 (charge loop); with word 0 bit 0x100 also plays 0x3F. */
s32 BtlParam_GetChargeLoopSound(BtlTechBChr *chr);

/* Common sound 0x17 (entering the powered-up state); with word 0 bit 0x100 also plays 0x40. */
s32 BtlParam_GetMaxPowerSound(BtlTechBChr *chr);

/* 1 unless the character has parameter flag 0x1000 and lacks ability 0x36. */
s32 BtlParam_CanFly(BtlTechBChr *chr);

/* ---- ki blasts (obj + 0x924) --------------------------------------------------------------------------------
 *
 * 13 records of 0x34 bytes, one per ki blast kind. Every quantity has three readers, in this order: of the blast
 * the fighter is firing now (kind from BtlKiBlast_GetCurrentKind), of the blast behind a hit record (owner and
 * kind from the record's shot: hit +0x68 -> side +0x10, kind +0x18), and of a kind given by the caller. The first
 * four functions are the ability and reaction adjustments those readers share.
 */

/* Ki blast damage after abilities: +50 % (0xA), then halved (0xB). The kind argument is unused. */
s32 BtlKiBlast_ScaleDamageByAbility(BtlTechBChr *chr, s32 damage, s32 kind);

/* Ki blast speed after abilities, uncharged kinds 0, 4, 8 only: x1.6 (0xE), else x1.4 (0xD), else x1.2 (0xC). */
f32 BtlKiBlast_ScaleSpeedByAbility(BtlTechBChr *chr, s32 kind, f32 speed);

/* Ki blast ki cost after abilities: doubled (0x2A), then halved (0x29). The kind argument is unused. */
s32 BtlKiBlast_ScaleKiByAbility(BtlTechBChr *chr, s32 ki, s32 kind);

/* With ability 0x4B and record type 0 or 1, the charged kinds give reaction 0x17 / 0x18 / 0x19 by charge level. */
s32 BtlKiBlast_MapReact(BtlTechBChr *chr, s32 react, s32 kind);

/* The same for the second reaction: 0x1A / 0x1B / 0x1C. */
s32 BtlKiBlast_MapReactS800(BtlTechBChr *chr, s32 react, s32 kind);

/* Kind 0..12 of the ki blast the fighter is firing, from its action (0x95), animation and charge; -1 if none. */
s32 BtlKiBlast_GetCurrentKind(BtlTechBChr *chr);

/* Record of the ki blast being fired (kind 0 when none); optionally returns the kind. */
BtlKiBlastData *BtlKiBlast_GetCurrent(BtlTechBChr *chr, s32 *outKind);

/* Record of the ki blast behind a hit record, with its owner and kind; NULL when the hit has no shot. */
BtlKiBlastData *BtlKiBlast_GetOfHit(BtlTechBHit *hit, BtlTechBChr **outChr, s32 *outKind);

/* Record of kind `kind` (kind 0 when out of range). */
BtlKiBlastData *BtlKiBlast_Get(BtlTechBChr *chr, u32 kind);

/* Record flags; bits 0 and 1 are dropped while BtlChar_TestMemberUnk70. */
s32 BtlKiBlast_GetFlags(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetFlagsOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetFlagsOf(BtlTechBChr *chr, u32 kind);

/* Damage of one hit: record damage * curve row 6, abilities, divided by the hit count when it is 2 or more. */
s32 BtlKiBlast_GetDamage(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetDamageOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetDamageOf(BtlTechBChr *chr, u32 kind);

/* Damage of one guarded hit: the same chain on record +0x08. */
s32 BtlKiBlast_GetGuardDamage(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetGuardDamageOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetGuardDamageOf(BtlTechBChr *chr, u32 kind);

/* Ki the shot costs (record +0x0C, abilities). */
s32 BtlKiBlast_GetKiCost(BtlTechBChr *chr);

/* The same for a hit record (an absorber gains three times this). */
s32 BtlKiBlast_GetKiCostOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetKiCostOf(BtlTechBChr *chr, u32 kind);

/* Flight speed per frame (record +0x10 in 10 km/h, abilities). */
f32 BtlKiBlast_GetSpeed(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetSpeedOfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetSpeedOf(BtlTechBChr *chr, u32 kind);

/* Homing turn rate in radians per frame (record +0x14 in degrees per second). */
f32 BtlKiBlast_GetTurnRate(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetTurnRateOfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetTurnRateOf(BtlTechBChr *chr, u32 kind);

/* Record +0x18 (seconds) in frames. */
s32 BtlKiBlast_GetFrames(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetFramesOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetFramesOf(BtlTechBChr *chr, u32 kind);

/* Record +0x31. */
s32 BtlKiBlast_GetUnk31(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetUnk31OfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetUnk31Of(BtlTechBChr *chr, u32 kind);

/* Reaction id of a hit (record +0x24, BtlKiBlast_MapReact). */
s32 BtlKiBlast_GetReact(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetReactOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetReactOf(BtlTechBChr *chr, u32 kind);

/* Reaction against a victim whose state has bit 0x800: record +0x25, or +0x24 when 0 (BtlKiBlast_MapReactS800). */
s32 BtlKiBlast_GetReactS800(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetReactS800OfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetReactS800Of(BtlTechBChr *chr, u32 kind);

/* Reaction against a victim whose state has bit 0x4000 or in action 0xDF: record +0x26, or +0x24 when 0. */
s32 BtlKiBlast_GetReactS4000(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetReactS4000OfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetReactS4000Of(BtlTechBChr *chr, u32 kind);

/* Reaction against a victim whose state has bit 0x200: record +0x27, or +0x24 when 0. */
s32 BtlKiBlast_GetReactS200(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetReactS200OfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetReactS200Of(BtlTechBChr *chr, u32 kind);

/* Record +0x02: type (spark module, sound class, deflect rules). */
s32 BtlKiBlast_GetType(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetTypeOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetTypeOf(BtlTechBChr *chr, u32 kind);

/* Record +0x03. */
s32 BtlKiBlast_GetUnk3(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetUnk3OfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetUnk3Of(BtlTechBChr *chr, u32 kind);

/* Record +0x30: number of hits. */
s32 BtlKiBlast_GetHits(BtlTechBChr *chr);

/* The same for a hit record. */
s32 BtlKiBlast_GetHitsOfHit(BtlTechBHit *hit);

/* The same for a kind. */
s32 BtlKiBlast_GetHitsOf(BtlTechBChr *chr, u32 kind);

/* Record +0x28 (float). */
f32 BtlKiBlast_GetUnk28(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetUnk28OfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetUnk28Of(BtlTechBChr *chr, u32 kind);

/* Record +0x2C (float). */
f32 BtlKiBlast_GetUnk2C(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetUnk2COfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetUnk2COf(BtlTechBChr *chr, u32 kind);

/* Knock-back speed of one hit: record +0x1C in 10 km/h, per frame, divided by the hit count. */
f32 BtlKiBlast_GetPush(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetPushOfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetPushOf(BtlTechBChr *chr, u32 kind);

/* Knock-back speed of one guarded hit: the same from record +0x20. */
f32 BtlKiBlast_GetGuardPush(BtlTechBChr *chr);

/* The same for a hit record. */
f32 BtlKiBlast_GetGuardPushOfHit(BtlTechBHit *hit);

/* The same for a kind. */
f32 BtlKiBlast_GetGuardPushOf(BtlTechBChr *chr, u32 kind);

/* ---- movement (obj + 0x928) ---------------------------------------------------------------------------------- */

/* Movement speed n per frame: table value in 10 km/h, x pose +0xAC for n 4 and 5, x curve row 8 except n 15 and 19, at most 4000 km/h. */
f32 BtlMoveParam_GetSpeed(BtlTechBChr *chr, s32 n);

/* Acceleration n per frame per frame (table +0x50 in 10 km/h per second). */
f32 BtlMoveParam_GetAccel(BtlTechBChr *chr, s32 n);

/* Table +0x58 (degrees) in radians. */
f32 BtlMoveParam_GetAngle58(BtlTechBChr *chr);

/* Table +0x5C + n * 4, times 10. */
f32 BtlMoveParam_GetHeight(BtlTechBChr *chr, s32 n);

/* Ki per frame of movement kind n (table +0x64 per second): kinds 0..2 free with ability 0x26, else halved with 0x25; kind 3 halved with 0x27. */
s32 BtlMoveParam_GetKiCost(BtlTechBChr *chr, s32 n);

/* Turn rate n in radians per frame (table +0x74 in degrees per second); x pose +0xAC for n 0. */
f32 BtlMoveParam_GetTurnRate(BtlTechBChr *chr, s32 n);

/* Table +0x80 + n * 4 (degrees per second) in radians per frame. */
f32 BtlMoveParam_GetTurnAccel(BtlTechBChr *chr, s32 n);

/* Table +0x90 + n * 4 (degrees) in radians. */
f32 BtlMoveParam_GetTurnMax(BtlTechBChr *chr, s32 n);

/* ---- techniques, slots 2..4 (obj + 0x92C) --------------------------------------------------------------------
 *
 * Every field of the table is an array of three, indexed by slot - 2. (The two flag words and the throw columns
 * match only when the index is formed first, `slot -= 2`; the others match with `[slot - 2]`.)
 */

/* Number of hits of technique slot 2..4: the product of its three factors, at least 1. */
s32 BtlSuper_GetHitCount(BtlTechBChr *chr, s32 slot);

/* First flag word of the technique. */
u32 BtlSuper_GetFlagsA(BtlTechBChr *chr, s32 slot);

/* Second flag word of the technique. */
u32 BtlSuper_GetFlags(BtlTechBChr *chr, s32 slot);

/* Technique id. */
s32 BtlSuper_GetId(BtlTechBChr *chr, s32 slot);

/* Table +0x1E (s16): compared with hit +0x8 by BtlColl_TryDodge. */
s32 BtlSuper_GetUnk1E(BtlTechBChr *chr, s32 slot);

/* Table +0x24 (seconds). */
f32 BtlSuper_GetShotTime(BtlTechBChr *chr, s32 slot);

/* Speed per frame of the technique's projectile (table +0x54 in 10 km/h). */
f32 BtlSuper_GetShotSpeed(BtlTechBChr *chr, s32 slot);

/* Turn rate in radians per frame (table +0x60 in degrees per second). */
f32 BtlSuper_GetShotTurnRate(BtlTechBChr *chr, s32 slot);

/* Table +0x6C (float). */
f32 BtlSuper_GetShotUnk6C(BtlTechBChr *chr, s32 slot);

/* Table +0x90 (s8; no caller found). */
s32 BtlSuper_GetUnk90(BtlTechBChr *chr, s32 slot);

/* First hit factor (number of shots), at least 1. */
s32 BtlSuper_GetShots(BtlTechBChr *chr, s32 slot);

/* Second hit factor, at least 1. */
s32 BtlSuper_GetHitsB(BtlTechBChr *chr, s32 slot);

/* Third hit factor: table byte + 1. */
s32 BtlSuper_GetHitsC(BtlTechBChr *chr, s32 slot);

/* Table +0x13B: how the hit direction and the recoil are derived. */
s32 BtlSuper_GetHitDirKind(BtlTechBChr *chr, s32 slot);

/* Table +0x13E: type of the technique; picks its action block (BtlAct_GetTechniqueAction). */
s32 BtlSuper_GetType(BtlTechBChr *chr, s32 slot);

/* Reaction id of a hit. */
s32 BtlSuper_GetReact(BtlTechBChr *chr, s32 slot);

/* Reaction of the second hit variant (hit flag 0x10); the first when not positive. */
s32 BtlSuper_GetReactAlt(BtlTechBChr *chr, s32 slot);

/* Reaction against a victim whose state has bit 0x800. */
s32 BtlSuper_GetReactS800(BtlTechBChr *chr, s32 slot);

/* The same for the second hit variant; BtlSuper_GetReactS800 when not positive. */
s32 BtlSuper_GetReactAltS800(BtlTechBChr *chr, s32 slot);

/* Table +0x14D (copied into the throw description). */
s32 BtlSuper_GetUnk14D(BtlTechBChr *chr, s32 slot);

/* Table +0x150: what a guard does against the technique. */
s32 BtlSuper_GetGuardKind(BtlTechBChr *chr, s32 slot);

/* Hit sound kind of the first / second hit variant. */
s32 BtlSuper_GetHitSound(BtlTechBChr *chr, s32 slot, s32 alt);

/* Number of steps of a rush, at least 1. */
s32 BtlSuper_GetStepCount(BtlTechBChr *chr, s32 slot);

/* Knock-back speed per frame (table +0x16C in 10 km/h). */
f32 BtlSuper_GetPush(BtlTechBChr *chr, s32 slot);

/* Knock-back speed through a guard (table +0x178). */
f32 BtlSuper_GetGuardPush(BtlTechBChr *chr, s32 slot);

/* Table damage * curve row 9 (slots 2, 3) or row 10 (slot 4); per hit unless `total`. */
s32 BtlSuper_GetBaseDamage(BtlTechBChr *chr, s32 slot, s32 total);

/* The same from the guard damage column. */
s32 BtlSuper_GetBaseGuardDamage(BtlTechBChr *chr, s32 slot, s32 total);

/* Ki the technique costs; halved with ability 0x2B. */
s32 BtlSuper_GetKiCost(BtlTechBChr *chr, s32 slot);

/* Damage the technique does to its user. */
s32 BtlSuper_GetRecoilDamage(BtlTechBChr *chr, s32 slot);

/* Table +0x1B4 (s32): amount drained during a rush. */
s32 BtlSuper_GetDrain(BtlTechBChr *chr, s32 slot);

/* Cooldown after the technique in frames (table +0x1C0 in seconds); stored in fighter +0xE40 on leaving. */
s32 BtlSuper_GetCooldownFrames(BtlTechBChr *chr, s32 slot);

/* Table +0x1CC (seconds) in frames: how long the charge type can be held. */
s32 BtlSuper_GetChargeLimitFrames(BtlTechBChr *chr, s32 slot);

/* Damage multiplier of a fully charged technique. */
f32 BtlSuper_GetChargeScale(BtlTechBChr *chr, s32 slot);

/* Table +0x1E4 (degrees) in radians; throw description +0x60. */
f32 BtlSuper_GetThrowAngleA(BtlTechBChr *chr, s32 slot);

/* Table +0x1F0 (degrees) in radians; throw description +0x64. */
f32 BtlSuper_GetThrowAngleB(BtlTechBChr *chr, s32 slot);

/* Speed per frame of the rush dash (table +0x1FC in 10 km/h). */
f32 BtlSuper_GetRushSpeed(BtlTechBChr *chr, s32 slot);

/* Character the technique's throw brings in: the table entry, or the alternate when the user is that character or (ids of 0x100 and above, flag 0x40000000) the user wears costume 1. */
s32 BtlSuper_GetThrowChara(BtlTechBChr *chr, s32 slot);

/* Costume for that character: the user's with flag 0x40000000, else 1 for technique 0x27F, else 0; 0 for ids of 0x100 and above. */
s32 BtlSuper_GetThrowCostume(BtlTechBChr *chr, s32 slot);

/* The user's gauge +0x20 when the entry is below 0x100 and the technique has flag 0x40000000, else 0. */
s32 BtlSuper_GetThrowGauge20(BtlTechBChr *chr, s32 slot);

/* Table +0x220 (s8; throw description +0x18). */
s32 BtlSuper_GetUnk220(BtlTechBChr *chr, s32 slot);

/* Table +0x223 (s8); 999 when negative. */
s32 BtlSuper_GetUnk223(BtlTechBChr *chr, s32 slot);

/* Table +0x226 (s8; throw description +0x2C). */
s32 BtlSuper_GetUnk226(BtlTechBChr *chr, s32 slot);

/* Table +0x229: row of the roster's prompt table. */
s32 BtlSuper_GetPromptRowIndex(BtlTechBChr *chr, s32 slot);

/* That row (roster +0x34, 0x14 bytes each). */
BtlTechBPromptRow *BtlSuper_GetPromptRow(BtlTechBChr *chr, s32 slot);

/* Table +0x165 (s8). */
s32 BtlSuper_GetUnk165(BtlTechBChr *chr, s32 slot);

/* Table +0x168, or the step count - 1 when negative. */
s32 BtlSuper_GetLastStep(BtlTechBChr *chr, s32 slot);

/* Table +0x22C (seconds) in frames. */
s32 BtlSuper_GetFrames22C(BtlTechBChr *chr, s32 slot);

/* Table +0x238 (seconds) in frames. */
s32 BtlSuper_GetFrames238(BtlTechBChr *chr, s32 slot);

/*
 * Damage of technique slot 2..4: of one hit, or of the whole technique when `total`; from the guard column when
 * `guard`. Each step rounds up to a multiple of 10 unless noted:
 *   base        table damage * curve row 9 (slots 2, 3) or row 10 (slot 4), divided by the hit count
 *   flag 0xA4   x 3 / 10 (the quick forms: powered-up combo finishers)
 *   flag 6      + 1 / 5, slots 2 and 3 only (powered-up state)
 *   flag 0x9C   + 1 / 10 (held flag the technique handlers set on input condition 0x6F)
 *   flag 0x98   + 3 / 10 when the technique has flag 0x8000 (0x98 is the held flag skill 0x18 sets)
 *   charge      + damage * techCharge * (chargeScale - 1), truncated, not rounded
 *   flag 0x10   of the technique: 1 when the opponent has ability 0x37 (not rounded)
 *   id 0x268    + 1 / 2, + 13 / 10 or + 25 / 10 at fighter +0xE5C == 1, 2, 3
 *   id 0x2CD    + (fighter +0xE60) / 5
 *   id 0x2D5    x the opponent's BtlParam_GetUnkC7Scale
 *   slot 4      + 1 / 5 with ability 0x6F
 *   ability 0x77  replaces everything by 999999 / hit count, also when `total` (not rounded)
 */
s32 BtlSuper_GetDamage(BtlTechBChr *chr, s32 slot, s32 guard, s32 total);

/* Position and yaw of the technique's cutscene on the current stage, entry n of 5. */
void BtlSuper_GetStagePlacement(BtlTechBChr *chr, s32 slot, s32 n, Vec4 *pos, Vec4 *rot);

/* 1 when any of the technique's four reactions is 0x22 (caught by a throw). */
s32 BtlSuper_IsThrow(BtlTechBChr *chr, s32 slot);

/* ---- skills, slots 0..1 (obj + 0x930) ------------------------------------------------------------------------ */

/* Number of hits of skill slot 0..1: the product of its three factors. */
s32 BtlSkill_GetHitCount(BtlTechBChr *chr, s32 slot);

/* First flag word of the skill (no caller found). */
u32 BtlSkill_GetFlagsA(BtlTechBChr *chr, s32 slot);

/* Second flag word of the skill. */
u32 BtlSkill_GetFlags(BtlTechBChr *chr, s32 slot);

/* Skill id. */
s32 BtlSkill_GetId(BtlTechBChr *chr, s32 slot);

/* Table +0x14 (s16; no caller found). */
s32 BtlSkill_GetUnk14(BtlTechBChr *chr, s32 slot);

/* Table +0x18 (float). */
f32 BtlSkill_GetShotTime(BtlTechBChr *chr, s32 slot);

/* Speed per frame of the skill's projectile (table +0x20 in 10 km/h). */
f32 BtlSkill_GetShotSpeed(BtlTechBChr *chr, s32 slot);

/* Turn rate in radians per frame (table +0x28 in degrees per second). */
f32 BtlSkill_GetShotTurnRate(BtlTechBChr *chr, s32 slot);

/* Table +0x30 (float). */
f32 BtlSkill_GetShotUnk30(BtlTechBChr *chr, s32 slot);

/* Table +0x38 (s8; no caller found). */
s32 BtlSkill_GetUnk38(BtlTechBChr *chr, s32 slot);

/* First hit factor, at least 1. */
s32 BtlSkill_GetShots(BtlTechBChr *chr, s32 slot);

/* Second hit factor, at least 1. */
s32 BtlSkill_GetHitsB(BtlTechBChr *chr, s32 slot);

/* Third hit factor: table byte + 1. */
s32 BtlSkill_GetHitsC(BtlTechBChr *chr, s32 slot);

/* Table +0x62: 4 = the hit direction is not taken from the attacker (BtlColl_HitByStrike). */
s32 BtlSkill_GetHitDirKind(BtlTechBChr *chr, s32 slot);

/* Table +0x64: which action block runs the skill (BtlAct_GetSkillAction). */
s32 BtlSkill_GetSequence(BtlTechBChr *chr, s32 slot);

/* Table +0x9E (s8). */
s32 BtlSkill_GetUnk9E(BtlTechBChr *chr, s32 slot);

/* Table +0x66: how long the skill's stat modifiers last (BTL_STAT_KIND_*). */
s32 BtlSkill_GetStatKind(BtlTechBChr *chr, s32 slot);

/* Reaction id of a hit. */
s32 BtlSkill_GetReact(BtlTechBChr *chr, s32 slot);

/* Reaction against a victim whose state has bit 0x800; the first when not positive. */
s32 BtlSkill_GetReactS800(BtlTechBChr *chr, s32 slot);

/* Hit sound kind. */
s32 BtlSkill_GetHitSound(BtlTechBChr *chr, s32 slot);

/* Knock-back of one hit: table +0x74 divided by the hit count. */
f32 BtlSkill_GetPush(BtlTechBChr *chr, s32 slot);

/* Knock-back of one guarded hit: table +0x7C divided by the hit count. */
f32 BtlSkill_GetGuardPush(BtlTechBChr *chr, s32 slot);

/* Damage (table +0x84); per hit unless `total`. */
s32 BtlSkill_GetDamage(BtlTechBChr *chr, s32 slot, s32 total);

/* Damage through a guard (table +0x8C); per hit unless `total`. */
s32 BtlSkill_GetGuardDamage(BtlTechBChr *chr, s32 slot, s32 total);

/* Blast gauge the skill costs: stocks (one less with ability 0x15, at least 1) * 100000. */
s32 BtlSkill_GetBlastCost(BtlTechBChr *chr, s32 slot);

/* Level the skill adds to stat 0 (table +0x96). */
s32 BtlSkill_GetStatLevel0(BtlTechBChr *chr, s32 slot);

/* Level the skill adds to stat 2 (table +0x98). */
s32 BtlSkill_GetStatLevel2(BtlTechBChr *chr, s32 slot);

/* Level the skill adds to stat 1 (table +0x9A). */
s32 BtlSkill_GetStatLevel1(BtlTechBChr *chr, s32 slot);

/* Level the skill adds to stat 3 (table +0x9C). */
s32 BtlSkill_GetStatLevel3(BtlTechBChr *chr, s32 slot);

/* Duration of the skill's effect (table +0xA0 in seconds) in frames. */
s32 BtlSkill_GetFrames(BtlTechBChr *chr, s32 slot);

/* Health the skill gives (negative: takes): table percent of the maximum health. */
s32 BtlSkill_GetHealthChange(BtlTechBChr *chr, s32 slot);

/* Ki the skill gives (negative: takes). */
s32 BtlSkill_GetKiChange(BtlTechBChr *chr, s32 slot);

/* Table +0xB8: second timed value (BtlSkill_Apply). */
s32 BtlSkill_GetValF(BtlTechBChr *chr, s32 slot);

/* Table +0xC0: first timed value (BtlSkill_Apply). */
s32 BtlSkill_GetValE(BtlTechBChr *chr, s32 slot);

/* ---- battle-level wrappers ------------------------------------------------------------------------------------
 *
 * Called by Battle_* (battle.c). The callees at 0x212F90..0x212FE0 are the next module's reset / init / term,
 * 0x22F9A8..0x22F9F0 a module that is told the number of views (2 in split screen, else 1), 0x218BA8..0x219648
 * the HUD, and BtlSeq_* the battle sequence.
 */

/* Round reset: resets the three modules and the sequence, and latches whether a replay is being played. */
void BtlGame_Reset(void);

/* Battle start: initialises the same modules; the 0x22F9C8 module gets 2 in split screen, else 1. */
void BtlGame_Init(void);

/* Battle end. */
void func_00304660(void) {
    Hud_Term();
    PauseMenu_Term();
    BtlPause_Term();
    BtlSeq_Term();
}

/* Before the fighters are updated: HUD pre-update, then the sequence's. */
void BtlGame_PreUpdate(void);

/* The sequence update; its result ends the battle loop. */
s32 BtlGame_Update(void);
