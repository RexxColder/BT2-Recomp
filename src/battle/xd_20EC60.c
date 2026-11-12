/*
 * BtlFacade_AreBothInterruptible (BT3 btl_facade.c, same code).
 */
#include "common.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "battle/btl_facade.h"
#include "battle/btl_seq.h"
#include "sys/math3d.h"

extern s32 func_0020A908(s32 side);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Returns 1 when both fighters are in an action the script may interrupt. */
extern s32 func_0020A908(s32 player);

s32 BtlFacade_AreBothInterruptible_20EC60(void) {
    if (func_0020A908(0) && func_0020A908(1)) {
        return 1;
    }
    return 0;
}
