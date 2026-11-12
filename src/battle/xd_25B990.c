/*
 * BtlFacade_ShakeCamera (BT3 btl_facade.c, same code).
 */
#include "common.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "battle/btl_facade.h"
#include "battle/btl_seq.h"
#include "sys/math3d.h"

extern void func_0025ACB8(f32 time);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Shakes the scripted camera at full strength for `time` seconds. */
extern void func_0025ACB8(f32 time);

s32 BtlFacade_ShakeCamera_25B990(f32 time) {
    func_0025ACB8(time);
    return 1;
}
