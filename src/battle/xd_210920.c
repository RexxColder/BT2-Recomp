/*
 * BtlOpp_GetDelta (BT3 btl_char_flag_opp.c, same code).
 */
#include "common.h"
#include "battle/btl_char_flag.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_00312650(Vec4 *dst, Vec4 *a, Vec4 *b);
extern BtlFlagPose *BtlChar_GetPos(BtlFlagChr *chr);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Vector from the fighter to the opponent's target position. */
extern void func_00312650(Vec4 *dst, Vec4 *a, Vec4 *b);

void BtlOpp_GetDelta(BtlFlagChr *chr, Vec4 *out) {
    Vec4 pos;

    BtlOpp_GetTargetPos(chr, &pos);
    func_00312650(out, &pos, &BtlChar_GetPos(chr)->pos);
}
