#include "common.h"
#include "battle/btl_tech_a.h"

/*
 * Fighter queries by side, the attack records and the character parameter block, 0x20BA80..0x20F0E8 (124 functions).
 * See include/battle/btl_tech_a.h for the record layouts and the attack id table.
 *
 * What the numbers are (each is the matching C below; the game terms are inferred from the callers):
 *   - damage of a hit        record +0x04 * attack curve (row 4: x0.5 at level -20, x1 at 0, x3 at 80), +-10% / x2 / x0.5
 *                            by ability, / number of hit events of the animation
 *   - ki charge              (param +0x30 or +0x34) / 30 + curve row 0 (-1000..0..+4000 per frame) + chr +0xE28 / 30,
 *                            x0.4 / 0.6 / 0.8 and x1.25 by ability, at least 200 per frame (ki maximum is 100000)
 *   - passive ki regen       param +0x38 / 30 + curve row 1 (-66..0..+266 per frame), up to param +0x28 (+ abilities)
 *   - ki-exhausted recovery  param +0x3C / 30 + curve row 2, x2 by ability, at least 10, until param +0x2C is reached
 *   - blast gauge            param +0x44 / 30 + curve row 3 (-33..0..+133 per frame), x1.2 / x0.5 / x0.8 by ability
 *   - max power              filled in param +0x50 / curve row 11 seconds, drained over param +0x54 + curve row 12
 *                            (0..8) seconds; the gauge is 30000
 *
 * Object boundary: unknown. The float pool 0x2FE0E4..0x2FE110 and the .rodata 0x2F1620..0x2F18F0 this file emits are
 * contiguous and exactly cover what the range owns; the neighbours on both sides (0x2FE0E0, 0x2FE114, jtbl_002F18F0)
 * belong to other functions, so the file links on its own whatever the original object was.
 *
 * No random draw. Non-simulation inputs, all in the BtlCtrl_* group (HUD queries, nothing they return feeds the
 * simulation here): the pad status (Pad.lastStatus), the battle mode, gProgress and the battle work flags.
 */

/* km/h to units per frame. This file's constants need this form (btl_char_move.c uses x * 1000 / 3600 * (1 / 30),
   which gives 0x3C17B424 for 1.0f where this file has 0x3C17B425). */
#define BTL_KMH(x) ((x) * (1000.0f / 3600.0f) / 30.0f)

extern BtlTechRoster *gBtlChars;
extern BtlTechProgress *gProgress;

extern BtlTechChr *BtlChar_FindBySide(s32 side);
extern BtlTechChr *BtlChar_Get(s32 player);
extern BtlTechObj *BtlChar_GetObj(BtlTechChr *chr);
extern BtlTechPad *BtlChar_GetPad(BtlTechChr *chr);
extern s32 BtlChar_IsFrozen(BtlTechChr *chr);
extern s32 BtlChar_IsDead(BtlTechChr *chr);
extern s32 BtlChar_TestMemberUnk70(BtlTechChr *chr);
extern s32 BtlChar_TestFlag(BtlTechChr *chr, s32 flag);
extern s32 BtlChar_IsFlagRaised(BtlTechChr *chr, s32 flag); /* set this frame and not the frame before */
extern s32 BtlOpp_GetPlayer(BtlTechChr *chr);
extern s32 BtlOpp_HasAbility(BtlTechChr *chr, s32 ability);
extern s32 BtlAct_GetCurrent(BtlTechChr *chr);
extern s32 BtlAct_IsAttackId(s32 action);
extern s32 BtlAct_TestPoweredSkill(BtlTechChr *chr, s32 bit);
extern s32 BtlAnim_GetId(BtlTechChr *chr);
extern f32 BtlAnim_GetFrame(BtlTechChr *chr);
extern BtlTechMember *BtlMember_Get(BtlTechChr *chr, s32 n);
extern BtlTechMember *BtlMember_GetActive(BtlTechChr *chr);
extern BtlTechGauge *BtlMember_GetActiveGauge(BtlTechChr *chr);
extern s32 BtlMember_CountAlive(BtlTechChr *chr);
extern s32 BtlMember_HasAbility(BtlTechChr *chr, s32 ability);
extern s32 BtlStat_GetMod(BtlTechChr *chr, s32 stat);
extern s32 BtlStat_GetKiChargeBonus(BtlTechChr *chr);
extern s32 BtlStat_GetKiRegenBonus(BtlTechChr *chr);
extern s32 BtlStat_GetKiRecoverBonus(BtlTechChr *chr);
extern s32 BtlStat_GetBlastGainBonus(BtlTechChr *chr);
extern f32 BtlStat_GetMeleeDamageScale(BtlTechChr *chr);
extern f32 BtlStat_GetGuardKiCostScale(BtlTechChr *chr);
extern f32 BtlStat_GetSpeedScale(BtlTechChr *chr);
extern f32 BtlStat_GetMaxPowerChargeScale(BtlTechChr *chr);
extern f32 BtlStat_GetMaxPowerExtraTime(BtlTechChr *chr);
extern s32 BtlUtil_Max(s32 a, s32 b);
extern BtlTechWork *Battle_GetWork(void);
extern BtlTechWork5A8 *Battle_GetWork5A8(void);
extern s32 Battle_GetMode(void);
extern s32 BtlSeq_GetState(void);

extern s32 BtlAct_CanUseTechnique(BtlTechChr *chr, s32 slot); /* slots 2..4 */
extern s32 BtlAct_CanUseSkill(BtlTechChr *chr, s32 slot); /* slots 0..1 */
extern s32 BtlCharApi_GetButtonIcon(BtlTechChr *chr, s32 cmd);  /* button 0..3 the key config gives command `cmd`, -1 if none */
extern s32 BtlSuper_GetPromptRowIndex(BtlTechChr *chr, s32 idx);  /* (obj + 0x92C)[0x227 + idx], signed */
/* Animation events of layer `layer` whose attribute word has a bit of `mask`: what 2 = frame of the last one,
   3 = how many there are. */
extern s32 BtlObjAnim_QueryEvent(BtlTechObj *obj, u64 mask, s32 layer, s32 what);

/* ---- queries by side -------------------------------------------------------------------------------------------- */

/* The opponent's +0xD50, 0 while the opponent is frozen or the battle flag 0x2000 is set. */
s32 BtlCtrl_GetOppUnkD50(s32 side);

/* BtlChar_GetObj behind an inline: the original calls it with jal (no tail call), which a direct `return f(chr)`
   does not give. */
static inline BtlTechObj *BtlCtrl_ObjOf(BtlTechChr *chr);

/* The battle object of the side's fighter. */
BtlTechObj *BtlCtrl_GetObj(s32 side);

/* Which of flags 0xDE..0xE2 the fighter has, as 0..4; -1 for none or while frozen. */
s32 BtlCtrl_GetFlagDEtoE2(s32 side);

/* The fighter's clash counter (+0xE50: compared to pick the winner of clashes B and C). */
s32 BtlCtrl_GetClashCount(s32 side);

/* Flag 6 (powered-up mode) was raised this frame. */
s32 BtlCtrl_IsFlag6Raised(s32 side);

/* Flag 0x71, 0 while frozen. */
s32 BtlCtrl_TestFlag71(s32 side);

/* Flag 5 (lock-on) was raised this frame, only in sequence state 3. */
s32 BtlCtrl_IsFlag5RaisedInFight(s32 side);

/* Flag 0xE3, 0 while frozen. */
s32 BtlCtrl_TestFlagE3(s32 side);

/* Flag 0x9C was raised this frame. */
s32 BtlCtrl_IsFlag9CRaised(s32 side);

/* Flag 0x9E was raised this frame. */
s32 BtlCtrl_IsFlag9ERaised(s32 side);

/* The active member has no health left. */
s32 BtlCtrl_IsDead(s32 side);

/* Flag 0x12B. */
s32 BtlCtrl_TestFlag12B(s32 side);

/* The fighter is in one of the member-switch actions 0xF3..0xF8. */
s32 BtlCtrl_IsSwitching(s32 side);

/* Flag 0xE4. */
s32 BtlCtrl_TestFlagE4(s32 side);

/* Flag 0xE5. */
s32 BtlCtrl_TestFlagE5(s32 side);

/* In battle mode 5: bit gProgress->unk7F4 of fighter 0's per-frame bit set. */
s32 BtlCtrl_TestProgressFrameBit(void);

/* Flag 0xE6 when the fighter's pad status is not 1; the status is written to *padStatus. */
s32 BtlCtrl_TestFlagE6Pad(s32 side, s32 *padStatus);

/* Flag 0xE6 when the fighter's pad status is 1. */
s32 BtlCtrl_TestFlagE6Pad1(s32 side);

/* Pad status 1 only: the technique prompt for the class picked by the held direction (it must be usable and the
   technique delay over) or else the watched class: the technique type row, its prompt kind 0..3 and the class. */
s32 BtlCtrl_GetTechPromptPad1(s32 side, s32 *row, s32 *kind, s32 *idx);

/* Other pad statuses, no direction class held: the button icons (1 or 2) to show for the watched technique class,
   a kind (2 with flag 0xA2, 1 with 0xA3, else 0), the pad status and the class. Fails if an icon is missing. */
s32 BtlCtrl_GetSwitchPrompt(s32 side, s32 *buttons, s32 *count, s32 *kind, s32 *padStatus, s32 *idx);

/* The button icon to show while one of flags 0xE7..0xEC is set (0xE7 is the ki-exhausted mash prompt), with kind 1
   (0xE7, 0xE8: buttons 0 / 2) or 2 (0xE9..0xEC: buttons 0x1B..0x1E). The last flag set wins. */
s32 BtlCtrl_GetChangePrompt(s32 side, s32 *button, s32 *kind, s32 *padStatus);

/* Sum of the modifiers of stat 0. */
s32 BtlCtrl_GetStatMod0(s32 side);

/* Sum of the modifiers of stat 2. */
s32 BtlCtrl_GetStatMod2(s32 side);

/* Sum of the modifiers of stat 1. */
s32 BtlCtrl_GetStatMod1(s32 side);

/* Sum of the modifiers of stat 3. */
s32 BtlCtrl_GetStatMod3(s32 side);

/* Whether skill slot 0..1 (BtlAct_CanUseSkill) or technique class 2..4 (BtlAct_CanUseTechnique) can be used now. */
s32 BtlCtrl_CanUseTechnique(s32 player, s32 slot);

/* Battle mode 3: work5A8.unk0, plus 1 once fighter 1 has nobody left, capped at work5A8.unk4. */
s32 BtlCtrl_GetWork5A8Count(void);

/* Sets the CPU level of every member of a fighter. */
void BtlCtrl_SetCpuLevel(s32 player, s32 level);

/* The active member's gauge word +0x30 is set. */
s32 BtlCtrl_TestMemberUnk70(s32 player);

/* ---- attack records --------------------------------------------------------------------------------------------- */

/* Row of an attack action in the roster's table. */
static inline BtlTechAtkAction *BtlAtk_GetActionRow(s32 n);

/* weak / medium / full record by charge */
#define TIER3(a, b, c)      \
    if (charge < mid) {     \
        return a;           \
    }                       \
    if (charge < full) {    \
        return b;           \
    }                       \
    return c

/* The id of the attack record the fighter's current action / animation uses, -1 when it is not attacking. */
s32 BtlAtk_GetId(BtlTechChr *chr);

/* The fighter's current attack record; ids outside 0..0xA2 (and -1) give record 0. The id used goes to *id. */
BtlAtkRecord *BtlAtk_GetRecord(BtlTechChr *chr, s32 *id);

/* Record `id` of the fighter's character. */
BtlAtkRecord *BtlAtk_GetRecordOf(BtlTechChr *chr, u32 id);

/* Damage changes by ability: ids 0..9 +10% (4) / -10% (5); ids 0x13..0x21 +10% (6) / -10% (7); ids 0x55, 0x56
   x2 (8) / halved (9). */
s32 BtlAtk_ApplyAbilities(BtlTechChr *chr, s32 val, u32 id);

/* Whether an attack id is one of 0x13..0x21. */
static inline s32 BtlAtk_IsId13to21(s32 id);

/* Record +0x26: which attack wins when two connect on the same frame. */
s32 BtlAtk_GetPriority(BtlTechChr *chr);

/* Damage of one hit: record damage * curve row 4, ability changes, divided by the animation's hit count. */
s32 BtlAtk_GetDamage(BtlTechChr *chr);

/* Damage of one guarded hit: the same chain on record +0x06, with -30% for ids 0..10 under skill effect 0x10. */
s32 BtlAtk_GetGuardDamage(BtlTechChr *chr);

/* Record +0x0C: first of two values the throw setup (0x1FC008) reads. */
s32 BtlAtk_GetThrowParamC(BtlTechChr *chr);

/* Record +0x0E: the second. */
s32 BtlAtk_GetThrowParamE(BtlTechChr *chr);

/* Ki the attacker gains per hit: record +0x0A, +50% (ability 0x6E) or +25% (0x20), divided by the hit count. */
s32 BtlAtk_GetKiGain(BtlTechChr *chr);

/* Ki the defender pays when it guards: record +0x08 * curve row 5, x2 (ability 0x44) or x1.5 (0x6D). */
s32 BtlAtk_GetGuardKiCost(BtlTechChr *chr);

/* Record +0x10 divided by the hit count: what a hit adds to the fighter's +0xD80 gauge (decays 400 per frame). */
s32 BtlAtk_GetUnk10(BtlTechChr *chr);

/* Reaction id, record +0x1B. */
s32 BtlAtk_GetReaction(BtlTechChr *chr);

/* Reaction id +0x1C (defender animation flag 0x800), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionB(BtlTechChr *chr);

/* Reaction id +0x1F (defender animation flag 0x4000 or action 0xDF), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionC(BtlTechChr *chr);

/* Reaction id +0x1D (defender animation flag 0x1000), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionD(BtlTechChr *chr);

/* Reaction id +0x1E (defender animation flag 0x2000), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionE(BtlTechChr *chr);

/* Record +0x20: stored in the defender's reaction block (+0xFB4). */
s32 BtlAtk_GetReactionSub(BtlTechChr *chr);

/* Reaction id +0x21 (defender animation flag 0x100, hit from the front), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionF(BtlTechChr *chr);

/* Reaction id +0x22 (defender animation 0xAE / 0xAF or flag 0x200), or +0x1B when it is 0. */
s32 BtlAtk_GetReactionG(BtlTechChr *chr);

/* Record +0x00: the attack's flag word. */
u32 BtlAtk_GetFlags(BtlTechChr *chr);

/* Push speed on hit: record +0x12 in units of 10 km/h, per frame. */
f32 BtlAtk_GetPushOnHit(BtlTechChr *chr);

/* Push speed on guard: record +0x13 in units of 10 km/h, per frame. */
f32 BtlAtk_GetPushOnGuard(BtlTechChr *chr);

/* Record +0x14 in units of 10 km/h, per frame, times curve row 8: the speed the attack handlers give the attacker. */
f32 BtlAtk_GetLaunchSpeed(BtlTechChr *chr);

/* Record +0x15 (degrees) in radians: yaw offset of the launch direction. */
f32 BtlAtk_GetLaunchAngleA(BtlTechChr *chr);

/* The same of record `id`. */
f32 BtlAtk_GetLaunchAngleAOf(BtlTechChr *chr, u32 id);

/* Record +0x16 (degrees) in radians: pitch of the launch direction. */
f32 BtlAtk_GetLaunchAngleB(BtlTechChr *chr);

/* The same of record `id`. */
f32 BtlAtk_GetLaunchAngleBOf(BtlTechChr *chr, u32 id);

/* Record +0x17 as a float: camera shake power on a hit. */
f32 BtlAtk_GetShakePower(BtlTechChr *chr);

/* Record +0x18 (tenths of a second) in seconds: camera shake time on a hit. */
f32 BtlAtk_GetShakeTime(BtlTechChr *chr);

/* Record +0x19 as a float: camera shake power on a guard. */
f32 BtlAtk_GetShakePowerB(BtlTechChr *chr);

/* Record +0x1A (tenths of a second) in seconds: camera shake time on a guard. */
f32 BtlAtk_GetShakeTimeB(BtlTechChr *chr);

/* Record +0x23: hit effect kind (1, 2 | 3, 4 | 10 pick the effect; non-zero sets effect bit 0x1D on the defender). */
s32 BtlAtk_GetHitFxKind(BtlTechChr *chr);

/* Record +0x24: level that picks the hit sound line. */
s32 BtlAtk_GetHitSoundLevel(BtlTechChr *chr);

/* Voice kind of the attack: record +0x25 mapped 1, 2, 3 -> 5, 6, 7; -1 (none) otherwise. */
s32 BtlAtk_GetVoiceKind(BtlTechChr *chr);

/* Guard result against guard kind 1 (record +0x29); result 1 becomes 0 when the opponent has ability 0x40. */
s32 BtlAtk_GetGuardKindA(BtlTechChr *chr);

/* Guard result against guard kind 2 (record +0x27); result 1 becomes 0 for ids 0x13..0x21 when the opponent has
   ability 0x40. */
s32 BtlAtk_GetGuardKindB(BtlTechChr *chr);

/* The same against guard kind 3 (record +0x28). */
s32 BtlAtk_GetGuardKindC(BtlTechChr *chr);

/* Rank of a guard result: 4 > 0 > 1 > 2 > 3. */
s32 BtlAtk_RankGuardKind(u32 kind);

/* Against guard kind 4: the highest-ranked of the record's three raw guard results (+0x29, +0x27, +0x28). */
s32 BtlAtk_GetBestGuardKind(BtlTechChr *chr);

/* Record +0x2A: guard result against guard kind 5. */
s32 BtlAtk_GetGuardKindE(BtlTechChr *chr);

/* Record +0x2B: 0 / 1 selects defender flag 0x66 / 0x67 on a guard. */
s32 BtlAtk_GetGuardFlagSel(BtlTechChr *chr);

/* Record +0x2C: armour levels the attack ignores. */
s32 BtlAtk_GetUnk2C(BtlTechChr *chr);

/* +0x2C of record `id`. */
s32 BtlAtk_GetUnk2COf(BtlTechChr *chr, u32 id);

/* The ki charge rate scaled by ability: x0.4 (0x31), x0.6 (0x30) or x0.8 (0x2F), then x1.25 (0x75). */
s32 BtlParam_ScaleKiCharge(BtlTechChr *chr, s32 val);

/* ---- character parameter block ---------------------------------------------------------------------------------- */

/* Parameter +0x10: flag word. */
u32 BtlParam_GetFlags(BtlTechChr *chr);

/* Parameter +0x14: skill bits. */
u32 BtlParam_GetFlags2(BtlTechChr *chr);

/* Parameter +0x18: skill bits that also need the powered-up mode. */
u32 BtlParam_GetFlags3(BtlTechChr *chr);

/* Parameter +0x00 (u16). */
s32 BtlParam_GetUnk0(BtlTechChr *chr);

/* Parameter +0x02: 4 is tested by the hit code (not thrown, not rushed). */
s32 BtlParam_GetUnk2(BtlTechChr *chr);

/* Parameter +0xAC: the transformation slot a neutral input picks. */
s32 BtlParam_GetUnkAC(BtlTechChr *chr);

/* Parameter +0x98 + slot: transformation target, 0xFF = none. */
s32 BtlParam_GetSlotId(BtlTechChr *chr, s32 slot);

/* Parameter +0x9C + slot, times 100000: blast gauge a transformation costs. */
s32 BtlParam_GetSlotCost(BtlTechChr *chr, s32 slot);

/* Parameter +0xA0 + slot. */
s32 BtlParam_GetSlotA0(BtlTechChr *chr, s32 slot);

/* Parameter +0xA4 + slot. */
s32 BtlParam_GetSlotA4(BtlTechChr *chr, s32 slot);

/* Parameter +0xA8 + slot. */
s32 BtlParam_GetSlotA8(BtlTechChr *chr, s32 slot);

/* Parameter +0xAD. */
s32 BtlParam_GetUnkAD(BtlTechChr *chr);

/* How many of the four transformation targets at +0x98 are not 0xFF. */
s32 BtlParam_CountSlots(BtlTechChr *chr);

/* Bit 4 + n of parameter +0xAD. */
s32 BtlParam_TestUnkADBit(BtlTechChr *chr, s32 n);

/* Parameter +0xB4 + n: fusion n. */
s32 BtlParam_GetUnkB4(BtlTechChr *chr, s32 n);

/* Parameter +0xB7 + n: fusion n. */
s32 BtlParam_GetUnkB7(BtlTechChr *chr, s32 n);

/* Parameter +0xBA + n * 4 + m: partner m of fusion n. */
s32 BtlParam_GetUnkBA(BtlTechChr *chr, s32 n, s32 m);

/* Parameter +0xAE + n, times 100000: blast gauge fusion n costs. */
s32 BtlParam_GetCostAE(BtlTechChr *chr, s32 n);

/* Parameter +0xC6. */
s32 BtlParam_GetUnkC6(BtlTechChr *chr);

/* Parameter +0xB1 + n: fusion n. */
s32 BtlParam_GetUnkB1(BtlTechChr *chr, s32 n);

/* Aura kind (passed to BtlObj_SetColorPreset on the object): parameter +0x03, replaced by 0..10 when the member has one of
   abilities 0x4D..0x53, 0x74, 0x54..0x56 (first match in that order). */
s32 BtlParam_GetAuraKind(BtlTechChr *chr);

/* Search type 0..9 of the active member's costume (parameter +0x58 + costume, costume above 3 reads 0); types 2..4
   become 7 (8 for type 4) while the member's gauge word +0x20 is set. */
s32 BtlParam_GetType(BtlTechChr *chr);

/* Radians per frame the search window widens, by search type; doubled by ability 0x6B (BtlAct_GrowWindow).
   The ten constants are written as literals: no expression was found for them (1.29, 1.58, 3.60, 6.31, 16.8, 1.26,
   1.74, 0.97, 1.12, 1.44 degrees per frame). The bits were compared with 0x2F1878. */
f32 BtlParam_GetTypeValueA(BtlTechChr *chr);

/* Distance per frame the search window grows, by search type (3000..40000 km/h); doubled by ability 0x6B. */
f32 BtlParam_GetTypeValueB(BtlTechChr *chr);

/* A third value by search type (0.1..0.5); no caller found. */
f32 BtlParam_GetTypeValueC(BtlTechChr *chr) {
    f32 tbl[BTL_TYPE_COUNT] = {
        0.15f, 0.2f, 0.4f, 0.45f, 0.5f, 0.2f, 0.35f, 0.1f, 0.15f, 0.2f,
    };

    return tbl[BtlParam_GetType(chr)];
}

/* The search type is 2..4 (the search action then plays animation 0x17F instead of 0x17E). */
s32 BtlParam_IsType2to4(BtlTechChr *chr);

/* The search type is 2, 3, 4, 6 or 9 (no caller found). */
s32 BtlParam_IsTypeSetA(BtlTechChr *chr);

/* The search type is 0..4, 6 or 9 (no caller found). */
s32 BtlParam_IsTypeSetB(BtlTechChr *chr);

/* How many class-0 ki blasts may be alive at once: parameter +0x80 less 3 / 2 / 1 by ability 0x11 / 0x10 / 0xF, but
   at least 1 when the raw value is positive. */
s32 BtlParam_GetCount80(BtlTechChr *chr);

/* Parameter +0x82: the same limit for class-1 blasts. */
s32 BtlParam_GetUnk82(BtlTechChr *chr);

/* Parameter +0x84 + n (n above 3 reads entry 0). */
s32 BtlParam_GetUnk84(BtlTechChr *chr, u32 n);

/* Parameter +0x88 + n (n above 1 reads entry 0). */
s32 BtlParam_GetUnk88(BtlTechChr *chr, u32 n);

/* Parameter +0x8A + n (n above 4 reads entry 0). */
s32 BtlParam_GetUnk8A(BtlTechChr *chr, u32 n);

/* Parameter +0x1C. */
s32 BtlParam_GetUnk1C(BtlTechChr *chr);

/* Parameter +0x20. */
s32 BtlParam_GetUnk20(BtlTechChr *chr);

/* Parameter +0x24. */
s32 BtlParam_GetUnk24(BtlTechChr *chr);

/* Ki level below which ki regenerates by itself: parameter +0x28 plus 60000 / 40000 / 20000 by ability 0x2E / 0x2D /
   0x2C, at most 100000. */
s32 BtlParam_GetKiRegenLimit(BtlTechChr *chr);

/* Parameter +0x2C: ki level that ends the ki-exhausted state (flag 0xBE). */
s32 BtlParam_GetGaugeB(BtlTechChr *chr);

/* Parameter +0x40. */
s32 BtlParam_GetUnk40(BtlTechChr *chr);

/* Ki gained per frame of charging: ((parameter +0x30) / 30 + curve row 0 + (fighter +0xE28) / 30) scaled by
   BtlParam_ScaleKiCharge, at least 200. */
s32 BtlParam_GetRateA(BtlTechChr *chr);

/* The same from parameter +0x34: used while the fighter has flag 0x11. */
s32 BtlParam_GetRateB(BtlTechChr *chr);

/* Ki regenerated per frame below BtlParam_GetKiRegenLimit: (parameter +0x38) / 30 + curve row 1, at least 0. */
s32 BtlParam_GetKiRegenRate(BtlTechChr *chr);

/* Ki recovered per frame in the ki-exhausted state (x4 by the caller on a button press): (parameter +0x3C) / 30 +
   curve row 2, doubled by ability 0x3C, at least 10. */
s32 BtlParam_GetKiRecoverRate(BtlTechChr *chr);

/* Ki actions 0x67..0x69 spend per frame: (parameter +0x4C) / 30, halved by ability 0x28. */
s32 BtlParam_GetKiDrain67(BtlTechChr *chr);

/* Parameter +0x48: ki an air recovery (actions 0x25..0x2A) costs; also tested by action 0xD5 / 0xD6 / 0xDF. */
s32 BtlParam_GetRecoverKiCost(BtlTechChr *chr);

/* Ki a vanishing step costs: 10000; 5000 with ability 0x23; 0 with ability 0x24. */
s32 BtlParam_GetAmountA(BtlTechChr *chr);

/* Ki vanishing behind the opponent costs: 20000; 10000 with ability 0x23; 0 with ability 0x24. */
s32 BtlParam_GetAmountB(BtlTechChr *chr);

/* Blast gauge gained per frame: (parameter +0x44) / 30 + curve row 3; x1.2 (ability 0x32), halved (0x1A), x0.8
   (0x33); at least 20. */
s32 BtlParam_GetBlastGainRate(BtlTechChr *chr);

/* Max power gained per frame of charging at full ki: 30000 (the whole gauge) divided by the frames in
   (parameter +0x50 seconds / curve row 11). */
s32 BtlParam_GetStepA(BtlTechChr *chr);

/* Max power lost per frame: 30000 divided by the frames in (parameter +0x54 + curve row 12) seconds, the time
   being at least one frame. */
s32 BtlParam_GetMaxPowerDrain(BtlTechChr *chr);
