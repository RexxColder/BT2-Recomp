/*
 * BtlMember_IsHealthEmpty (BT3 btl_char_member.c, same code).
 */
#include "common.h"
#include "battle/btl_char_member.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Whether the active member has no health left. */
s32 BtlMember_IsHealthEmpty_2127F8(BtlMemberChr *chr) {
    return BtlMember_GetActiveGauge(chr)->health <= 0;
}
