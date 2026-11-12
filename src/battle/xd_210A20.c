/*
 * BtlOpp_GetDistance (BT3 btl_char_flag_opp.c, same code).
 */
#include "common.h"
#include "battle/btl_char_flag.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern f32 func_0029DFD0(Vec4 *v);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Distance to the opponent. */
extern f32 func_0029DFD0(Vec4 *v);

f32 BtlOpp_GetDistance(BtlFlagChr *chr) {
    Vec4 d;

    BtlOpp_GetDelta(chr, &d);
    return func_0029DFD0(&d);
}
